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

-- 根据结构查看2023年7月28日Humphrey街的记录
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';


-- 根据现场报告查看面包店的信息
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND hour > 9;

-- 根据面包店纪录中的车牌寻找嫌疑人的信息
SELECT name, phone_number,passport_number, bakery_security_logs.day  FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.day = 28;

SELECT * FROM phone_calls;
