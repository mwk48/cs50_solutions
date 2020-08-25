SELECT movies.title, ratings.rating FROM "movies"
JOIN "ratings" ON movies.id=ratings.movie_id where movie_id in (SELECT id FROM "movies" where year==2010)
ORDER BY ratings.rating DESC ,title