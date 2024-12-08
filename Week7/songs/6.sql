SELECT name FROM songs WHERE id IN (SELECT id FROM artists WHERE name = "Post Malone");
