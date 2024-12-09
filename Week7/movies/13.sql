SELECT COUNT(name) FROM people WHERE ID IN
(
    SELECT DISTINCT person_id FROM stars
    WHERE movie_id IN (
        SELECT movie_id FROM stars
        WHERE person_id= (
            SELECT id FROM people
            WHERE name = 'Kevin Bacon'
            AND birth = 1958
        )
    )
) AND name != 'Kevin Bacon';

SELECT name FROM people
JOIN stars ON people.id = s2.person_id
JOIN stars s2 ON s2.movie_id =
WHERE stars.movie_id
