-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 根据已知线索查看犯罪现场报告的2023年7月28日 Humphrey 街
-- 查看犯罪现场报告的结构
.schema crime_scene_reports
-- 根据结构查看2023年7月28日Humphrey街的记录
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey';
