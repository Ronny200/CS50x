-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 查看犯罪现场报告的结构
.schema crime_scene_reports

-- 根据结构查看2023年7月28日Humphrey街的记录
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';

-- 根据现场报告查看面包店的信息
.scheme bakery_security_logs
