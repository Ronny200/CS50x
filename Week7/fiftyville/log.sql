-- Keep a log of any SQL queries you execute as you solve the mystery.

-- airports              -- 机场
-- crime_scene_reports   -- 犯罪现场报告
-- people                -- 人员
-- atm_transactions      -- 自动取款机交易
-- flights               -- 航班
-- phone_calls           -- 电话
-- bakery_security_logs  -- 面包店安全日志
-- interviews            -- 采访
-- bank_accounts         -- 银行账户
-- passengers            -- 乘客

-- 查看2023年7月28日Humphrey street的犯罪记录获知鸭子被盗时间为10:15
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street' AND description LIKE '%CS50%';

/** 根据采访记录可以判断：
    1. 小偷在盗窃的10分钟内从面包店停车场上车也就是 28 日 10:15 -- 10:25 阶段走的
    2. 小偷在28日早上去Leggett Street街道的银行提款机取过钱
    3. 小偷在离开面包店的时候打了电话，通话时间不到一分钟。在电话中，我听到小偷说他们计划明天乘坐最早一班从 Fiftyville 出发的航班离开。然后小偷让电话另一端的人帮他们购买机票。
*/
SELECT transcript FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28
AND transcript LIKE '%thief%';

-- 根据线索查看面包店10:15 -- 10:25之间离开的人
-- | Barry   |
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Kelsey  |
-- | Luca    |
-- | Sofia   |
-- | Vanessa |
SELECT name FROM people
JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
WHERE day = 28 AND hour > 9 and minute > 14 and hour < 11 and minute < 26
ORDER BY name;


-- 根据线索查看10:15 -- 10:25通多电话的人
-- | Sofia   |
-- | Kelsey  |
-- | Bruce   |
-- | Kelsey  |
-- | Taylor  |
-- | Diana   |
-- | Carina  |
-- | Kenny   |
-- | Benista |
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE month = 7 AND day = 28 AND duration < 60;

-- 根据线索查看28号早上取过钱的人
SELECT * FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- 通过银行账号获取取钱人的信息
SELECT people.name, passport_number, phone_number, license_plate FROM people
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
WHERE
    atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw';

-- 通过上面线索进行过滤
SELECT DISTINCT people.name, people.passport_number FROM people
JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls
    ON people.phone_number = phone_calls.caller
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
WHERE
    atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour > 9
    AND bakery_security_logs.minute >14
    AND bakery_security_logs.hour < 11
    AND bakery_security_logs.minute < 26;

根据所有线索先追踪小偷
SELECT DISTINCT people.name, airports.city FROM people
JOIN passengers
    ON people.passport_number = passengers.passport_number
JOIN flights
    ON passengers.flight_id = flights.id
JOIN airports
    ON flights.destination_airport_id = airports.id
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls
    ON people.phone_number = phone_calls.caller
WHERE
    atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour > 9
    AND bakery_security_logs.minute >14
    AND bakery_security_logs.hour < 11
    AND bakery_security_logs.minute < 26
    AND flights.month = 7
    AND flights.day = 29
    AND airports.id = 8;









