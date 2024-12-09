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
AND street = 'Humphrey Street' AND description LIKE '%thief%';

/** 根据采访记录可以判断：
    1. 小偷在盗窃的10分钟内从面包店停车场上车也就是 10:15 -- 10:25阶段走的
    2. 小偷在早上去Leggett Street街道的银行提款机取过钱
    3. 小偷在10:15 -- 10:25 阶段给同伙打过电话，计划7月29日坐飞机离开
*/
SELECT transcript FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28
AND transcript LIKE '%thief%';

-- 根据线索查看面包店10:15 -- 10:25之间离开的人
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND hour > 9 and minute > 14 and hour < 11 and minute < 26;

-- 根据线索查看10:15 -- 10:25通多电话的人
SELECT caller FROM phone_calls
WHERE month = 7 AND day = 28;

-- 根据线索查看28号早上取过钱的人
SELECT * FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- 通过银行账号获取取钱人的名字，电话，车牌
SELECT * FROM people
JOIN 
