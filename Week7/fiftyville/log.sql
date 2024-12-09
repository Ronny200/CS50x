-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 根据结构查看2023年7月28日Humphrey街的记录
.schema crime_scene_reports

SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';
-- CS50 鸭子被盗事件发生在上午 10:15
-- 事发地点位于 Humphrey Street 面包店
-- 今天采访了当时在场的三名目击者——每人的采访记录都提到了这家面包店
-- 乱扔垃圾事件发生在 16:36。没有已知目击者

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
SELECT * FROM bakery_security_logs
WHERE day = 28 AND hour < 11;
