SELECT name FROM "people"
JOIN "stars" ON people.id=stars.person_id
JOIN "movies" ON movies.id=stars.movie_id where movie_id = (SELECT id FROM "movies" where "title" = 'Toy Story')