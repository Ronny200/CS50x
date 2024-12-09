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

SELECT COUNT(DISTINCT p2.name) FROM people p1
JOIN stars s1 ON p1.id = s1.person_id
JOIN stars s2 ON s1.movie_id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Kevin Bacon'
AND p1.birth = '1958'
AND p2.name != 'Kevin Bacon';
