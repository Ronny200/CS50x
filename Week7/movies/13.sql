SELECT COUNT(*) FROM stars WHERE movie_id =
(SELECT movie_id FROM stars WHERE person_id=
    (SELECT id FROM people
     WHERE name = 'Kevin Bacon' AND birth = 1958));

