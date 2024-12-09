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

/** 根据采访记录可以判断：
    1. 小偷在盗窃的10分钟内从面包店停车场上车也就是 10:15 -- 10:25阶段走的
    select * from bakery_security_logs  where year = 2023 and month = 7 and day = 28 and hour >9 and minute > 14 and hour < 11 and minute < 26;
    2. 小偷在早上去银行提款机取过钱
    3. 小偷在10:15 -- 10:25 阶段给同伙打过电话，计划7月29日坐飞机离开
*/


-- 查看2023年7月28日Humphrey街的犯罪记录获知鸭子被盗时间为10:15
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street' AND description LIKE '%thief%';

/** 根据采访记录可以判断：
    1. 小偷在盗窃的10分钟内从面包店停车场上车也就是 10:15 -- 10:25阶段走的
    2. 小偷在早上去银行提款机取过钱
    3. 小偷在10:15 -- 10:25 阶段给同伙打过电话，计划7月29日坐飞机离开
*/
SELECT transcript FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28
AND transcript LIKE '%thief%';

-- 根据线索查看面包店10:15 -- 10:25之间离开的人
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND hour > 9 and minute > 14 and hour < 11 and minute < 26;

-- 根据面包店纪录中的车牌寻找嫌疑人的信息
SELECT DISTINCT name, phone_number,passport_number, bakery_security_logs.day  FROM people
JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
WHERE bakery_security_logs.day = 28;

SELECT * FROM atm_transactions ;
