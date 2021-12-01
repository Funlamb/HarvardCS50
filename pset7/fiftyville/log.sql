-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

-- >.tables : To see what is in the DB
-- >.schema crime_scene_reports : To see what is in the crime_scene_reports

-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );

-- >SELECT description FROM crime_scene_reports WHERE YEAR = 2020 AND month = 7 AND day = 28 AND street LIKE "Chamberlin Street";
--      Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
--      Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- >.schema interviews
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );

-- >SELECT year, transcript FROM interviews;
-- Just wanted to see how many interviews there were in the DB

-- >.schema
-- Wanted to see how the DB was orginized

-- SELECT name FROM interviews WHERE day = 28 AND year = 2020 AND month = 7;
-- Forgot to add the transcript.

-- SELECT name, transcript FROM interviews WHERE day = 28 AND year = 2020 AND month = 7;

-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
--      If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. 
--      Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. 
--      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--      The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- SELECT caller, receiver, duration FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020;
-- Too complicated to make an assumption on who it is. Need to figure out what the duration integer is in units.

SELECT license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
-- Hoping to find our more about the vehicales that where near the scene of the crime

SELECT license_plate, hour, minute, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
-- Trying to get a more detailed view with times

SELECT atm_location FROM atm_transactions;
-- Looked at what locations were in DB

SELECT transaction_type, amount FROM atm_transactions WHERE atm_location LIKE "Fifer Street" AND year = 2020 AND month = 7 AND day = 28;
-- Showed transactions but nothing of inrest yet

