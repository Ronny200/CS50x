SELECT title FROM movies
JOIN people ON people.name = 'Chadwick Boseman'
JOIN stars ON stars.person_id = people.id
JOIN ratings ON ratings.movie_id = stars.movie_id
WHERE 
;

