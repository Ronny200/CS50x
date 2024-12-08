SELECT (DISTINCT name) FROM people
JOIN directors ON people.id = directors.person_id
JOIN 
