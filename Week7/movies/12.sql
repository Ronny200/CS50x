SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movies.id in (
    SELECT stars.movie_id FROM stars
    JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Bradley Cooper')
AND(
    SELECT stars.movie_id FROM stars
    JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Jennifer Lawrence')
GROUP BY title;

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name in ('Jennifer Lawrence', 'Bradley Cooper')
GROUP BY movies.title
HAVING COUNT(DISTINCT people.name) = 2;
