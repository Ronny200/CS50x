-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 根据结构查看2023年7月28日Humphrey街的记录
.schema crime_scene_reports

SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';


-- 根据现场报告查看面包店的结构和信息
.scheme bakery_security_logs

SELECT hour, minute, activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND hour < 11;



