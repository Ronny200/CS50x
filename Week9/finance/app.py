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
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    usd_cash = usd(user_cash[0]["cash"])
    user_shares = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)
    return render_template("index.html", user_cash = usd_cash, shares = user_shares)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_num = int(request.form.get("shares"))
        shares = lookup(symbol)
        if symbol == "":
            return apology("missing symbol", 400)
        elif shares_num == None:
            return apology("missing Shares", 400)
        elif shares  == None:
            return apology("missing symbol", 400)
        else:
            user_id = session["user_id"]
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
            shares_price = shares["price"]
            shares_total_price = shares_price * shares_num
            if shares_total_price > user_cash:
                return apology("can't afford", 400)
            else:
                new_cash = round(user_cash - shares_total_price, 2)

            try:
                # 检查是否已存在当前股票
                exist_shares = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?", user_id, symbol)
                if exist_shares:
                    # 获取需要更新的数值
                    new_shares = int(exist_shares[0]["shares"]) +shares_num
                    new_price = shares_price
                    new_total = round(exist_shares[0]["total"] + shares_total_price, 2)

                    # 更新sql
                    db.execute("UPDATE shares SET shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                                new_shares, new_price, new_total, user_id, symbol)

                    # 添加新历史记录
                    db.execute("INSERT INTO history (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                                user_id, symbol, shares_num, shares_price, shares_total_price)

                    # 更新余额
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
                    return redirect("/")
                else:
                    # 添加新股票
                    db.execute("INSERT INTO shares (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                                user_id, symbol, shares_num, shares_price, shares_total_price)

                    # 添加新历史记录
                    db.execute("INSERT INTO history (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                                user_id, symbol, shares_num, shares_price, shares_total_price)
                    # 更新余额
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", round(user_cash -
                                shares_total_price, 2), user_id)
                    return redirect("/")

            except ValueError as e:
                return apology(f"{e}", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)
    return render_template("history.html", history = history)


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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = lookup(symbol)
        if symbol == "":
            return apology("missing symbol", 400)
        elif shares  == None:
            return apology("missing symbol", 400)
        else:
            print(shares)
            return render_template("quoted.html", shares = shares)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "POST":

        # 对表单开始检查
        if not request.form.get("username"):
            return apology("missing username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("missing password", 400)

        elif not request.form.get("confirmation"):
            return apology("passwords dont't match", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords dont't match", 400)

        # 将新用户添加到数据库
        name = request.form.get("username")
        passwd = generate_password_hash(request.form.get("password"))
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, passwd)
            session["user_id"] = name
            return redirect("/")
        except ValueError:
            return apology("username taken", 400)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    shares_all = db.execute("SELECT * FROM shares WHERE user_id = ?", user_id)
    sell_shares = request.form.get("shares")
    sell_symbol = request.form.get("symbol")
    current_share = lookup(sell_symbol)
    sell_price = current_share["price"]
    sell_total_price = round(sell_price * sell_shares, 2)
    sql_shares = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?", user_id, sell_symbol)
    if request.method == "POST":
        if sell_symbol == "":
            return apology("Missing Symbol", 400)
        elif sell_shares == "":
            return apology("Missing shares", 400)
        elif not sql_shares:
            return apology("Missing shares", 400)
        else:
            sql_shares = int(sql_shares[0]["shares"])
            sell_shares = int(sell_shares)
            if sell_shares > sql_shares:
                return apology("Too many shares", 400)
            try:
                new_shares = sql_shares - sell_shares
                new_price = shares_price
                new_total = round(exist_shares[0]["total"] + shares_total_price, 2)

                # 更新sql
                db.execute("UPDATE shares SET shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                            new_shares, new_price, new_total, user_id, symbol)

                # 添加新历史记录
                db.execute("INSERT INTO history (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                            user_id, symbol, shares_num, shares_price, shares_total_price)

                # 更新余额
                db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
                return redirect("/")
            except ValueError as e:
                return apology(f"{e}", 400)


    else:
        return render_template("sell.html", symbols = shares_all)
