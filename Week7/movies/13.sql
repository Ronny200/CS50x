SELECT name FROM people WHERE people.id IN
(SELECT movie_id FROM stars WHERE person_id=
    (SELECT id FROM people
     WHERE name = 'Kevin Bacon' AND birth = 1958));

