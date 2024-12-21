from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    try:
        get_user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_shares = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)
        user_cash = get_user_cash[0]["cash"]
        print(user_shares)
        for share in user_shares:
            current_info = lookup(share["symbol"])
            share["price"] = current_info["price"]
            share["total"] = current_info["price"] * int(share["shares"])
            
            print(share["symbol"], share["price"], share["shares"], share["total"])
        return render_template("index.html", user_cash = user_cash, shares = user_shares)
    except Exception as err:
        return apology(f"{err}", 400)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # 清理获取的数据
        symbol = request.form.get("symbol").strip()
        shares_str = request.form.get("shares").strip()

        # 检测股票代码是否为空
        if not symbol:
            return apology("missing symbol", 400)

        # 检测股票数量是否为空或者不为数字
        if not shares_str.isdigit() or int(shares_str) <= 0:
            return apology("missing Shares", 400)

        # 股票数量转为数字并通过lookup获取股票信息
        shares_num = int(shares_str)
        shares_info = lookup(symbol)

        # 检测股票信息是否错误
        if not shares_info:
            return apology("missing Shares", 400)

        user_id = session["user_id"]

        # 从数据库获取用户当前资金
        user_cash_result = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_result[0]["cash"]

        # 获取股票当前价格和购买的总价
        shares_price = shares_info["price"]
        shares_total_price = shares_price * shares_num

        # 判断是否有足够的资金购买股票
        if shares_total_price > user_cash:
            return apology("can't afford", 400)
        else:
            new_cash = round(user_cash - shares_total_price, 2)

        try:
            # 检查数据库是否已存在当前股票
            exist_shares = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?", user_id, symbol)

            # 更新数据库中的股票数据
            if exist_shares:
                new_shares = exist_shares[0]["shares"] + shares_num
                new_price = shares_price
                new_total = round(exist_shares[0]["total"] + shares_total_price, 2)

                db.execute("UPDATE shares SET shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                            new_shares, new_price, new_total, user_id, symbol)

            # 添加新股票
            else:
                db.execute("INSERT INTO shares (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                            user_id, symbol, shares_num, shares_price, shares_total_price)


            # 刷新现有资金
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

            # 添加购买历史记录
            db.execute("INSERT INTO history (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                        user_id, symbol, shares_num, shares_price, shares_total_price)

            return redirect("/")

        except Exception as err:
            return apology(f"buy error:\n{err}", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    try:
        history = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)
        return render_template("history.html", history = history)
    except Exception as err:
        return apology(f"show history error:\n{err}", 400)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    """查询股价"""
    if request.method == "POST":
        symbol = request.form.get("symbol").strip()
        if not symbol:
            return apology("missing symbol", 400)

        shares_info = lookup(symbol)
        if not shares_info:
            return apology("missing symbol", 400)

        return render_template("quoted.html", shares = shares_info)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # 对表单开始检查
        if not username:
            return apology("missing username", 400)

        elif not password:
            return apology("missing password", 400)

        elif not confirmation:
            return apology("passwords dont't match", 400)

        elif password != confirmation:
            return apology("passwords dont't match", 400)

        # 检查用户名是否已被占用
        exist_username = db.execute("SELECT * FROM users WHERE username = ?", username)
        if exist_username:
            return apology("username is existing", 400)

        # 将新用户添加到数据库
        try:
            password_hashed = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hashed)

            user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]["id"]
            session["user_id"] = user_id
            return redirect("/")

        except Exception as err:
            return apology(f"username taken\n{err}", 400)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        # 获取要售卖的股票代码和数量
        sell_shares_str = request.form.get("shares")
        sell_symbol = request.form.get("symbol")

        if sell_symbol == "":
            return apology("Missing Symbol", 400)

        if sell_shares_str == "":
            return apology("Missing shares", 400)

        if not sell_shares_str.isdigit() or int(sell_shares_str) <= 0:
            return apology("Missing shares", 400)

        current_shares = lookup(sell_symbol)
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        sql_shares_info = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?", user_id, sell_symbol)
        sql_shares = int(sql_shares_info[0]["shares"])
        sql_total = int(sql_shares_info[0]["total"])

        sell_shares = int(sell_shares_str)
        sell_price = current_shares["price"]
        sell_total_price = round(sell_price * sell_shares, 2)

        if sell_shares > sql_shares:
            return apology("Too many shares", 400)

        try:
            new_shares = sql_shares - sell_shares
            new_cash = round(user_cash + sell_total_price, 2)
            new_total = round(sql_total - sell_total_price)

            # 更新sql
            db.execute("UPDATE shares SET shares = ?, total = ? WHERE user_id = ? AND symbol = ?",
                            new_shares,  new_total, user_id, sell_symbol)

            # 添加新历史记录
            db.execute("INSERT INTO history (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                        user_id, sell_symbol, -sell_shares, sell_price, sell_total_price)

            # 更新余额
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

            # 当手中持有股票数量为0，则删除股票记录
            if new_shares == 0:
                db.execute("DELETE FROM shares WHERE user_id = ? AND symbol = ?", user_id, sell_symbol)

            return redirect("/")

        except Exception as err:
            return apology(f"{err}", 400)

    else:
        shares_all = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)
        return render_template("sell.html", symbols = shares_all)
