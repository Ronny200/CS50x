SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON stars.person_id = people.id
JOIN people WHERE people.name = 'Chadwick Boseman'
ORDER BY rating
LIMIT 5;

