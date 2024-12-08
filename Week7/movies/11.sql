SELECT title FROM people
JOIN stars ON person.id = stars.movie_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id ratings.movie_id
WHERE person.id = 'Chadwick Boseman'
ORDER BY rating
LIMIT 5;


