-- SELECT title FROM movies
-- JOIN stars s1 ON movies.id = s1.movie_id
-- JOIN stars s2 ON movies.id = s2.movie_id
-- JOIN people p1 ON s1.person_id = p1.id
-- JOIN people p2 ON s2.person_id = p2.id
-- WHERE p1.name = 'Jennifer Lawrence'
-- AND p2.name = 'Bradley Cooper';

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name in ('Jennifer Lawrence', 'Bradley Cooper')
GROUP BY movies.title
HAVING COUNT(DISTINCT people.name) = 2;
