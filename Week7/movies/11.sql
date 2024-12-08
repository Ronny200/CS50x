SELECT title FROM movies



JOIN ratings ON movies.id = ratings.movie_id
JOIN people ON 
ORDER BY ratings.rating
LIMIT 5;
