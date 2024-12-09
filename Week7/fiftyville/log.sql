-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 根据结构查看2023年7月28日Humphrey街的记录
.schema crime_scene_reports

SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';


-- 根据现场报告查看面包店的信息
.scheme bakery_security_logs
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND hour < 11;

-- 怀疑对象为10：00-10:23出门的人
-- | 10   | 16     | exit     | 5P2BI95       |
-- | 10   | 18     | exit     | 94KL13X       |
-- | 10   | 18     | exit     | 6P58WS2       |
-- | 10   | 19     | exit     | 4328GD8       |
-- | 10   | 20     | exit     | G412CB7       |
-- | 10   | 21     | exit     | L93JTIZ       |
-- | 10   | 23     | exit     | 322W7JE       |
-- | 10   | 23     | exit     | 0NTHK55       |
-- | 10   | 35     | exit     | 1106N58

