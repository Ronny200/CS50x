SELECT person_id FROM stars WHERE
(SELECT id FROM people
WHERE name = 'Kevin Bacon' AND birth = 1958;)

