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
SELECT DISTINCT name FROM people
JOIN bakery_security_logs bsl
    ON bsl.license_plate = people.license_plate
WHERE month = 7 AND day = 28
    AND hour = 10 AND minute > 15 AND minute < 25
    AND activity = 'exit'
ORDER BY name;


-- 根据线索查看10:15 -- 10:25通电话的人
-- | Benista |
-- | Bruce   |
-- | Carina  |
-- | Diana   |
-- | Kelsey  |
-- | Kenny   |
-- | Sofia   |
-- | Taylor  |
SELECT DISTINCT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE month = 7 AND day = 28 AND duration < 60
ORDER BY name;

-- 通过银行账号获取取钱人的信息
-- | Benista |
-- | Brooke  |
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Kenny   |
-- | Luca    |
-- | Taylor  |
SELECT DISTINCT name FROM people
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
WHERE
    atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
ORDER BY name;

-- 29日最早的从cs50起飞的航班
-- | 36 |
SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville' and flights.day = 29
ORDER BY hour, minute limit 1;

-- 根据所有线索先追踪小偷.
-- | Bruce |
SELECT DISTINCT p.name FROM people p
JOIN passengers ps ON p.passport_number = ps.passport_number AND ps.flight_id = 36
JOIn phone_calls pc ON pc.caller = p.phone_number AND pc.day = 28 AND pc.duration < 60
JOIN bakery_security_logs bsl ON bsl.license_plate = p.license_plate
    AND bsl.activity = 'exit' AND bsl.day = 28
    AND bsl.hour = 10 AND bsl.minute > 15 AND bsl.minute < 25
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
    AND at.month = 7 AND at.day = 28
    AND at.atm_location = 'Leggett Street'
    AND at.transaction_type = 'withdraw';

-- 确定小偷要去的城市
-- | New York City |
SELECT a.city FROM airports a
JOIN flights f ON f.destination_airport_id = a.id
JOIN passengers pe ON pe.flight_id = f.id
JOIN people p ON p.passport_number = pe.passport_number
WHERE p.name = 'Bruce';

-- 小偷的同伙为和小偷通话的人
| Robin |
SELECT p.name FROM people p
JOIN phone_calls pc ON p.phone_number = pc.receiver AND month = 7 AND day = 28 AND duration < 60
JOIN people p2 ON p2.phone_number = pc.caller
WHERE p2.name = 'Bruce';

