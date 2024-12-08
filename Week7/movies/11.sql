SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
ORDER BY ratings.rating
LIMIT 5;
