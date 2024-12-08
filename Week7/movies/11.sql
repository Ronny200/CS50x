SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating
LIMIT 5;

