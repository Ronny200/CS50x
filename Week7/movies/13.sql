SELECT name FROM people

JOIN stars ON stars.person_id = people.id
WHERE people.name in 'Kevin Bacon' AND birth = 1985;
