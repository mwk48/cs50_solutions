SELECT distinct(title) from "movies"
join "ratings" ON ratings.movie_id=movies.id
JOIN "stars" ON movies.id=stars.movie_id
where stars.movie_id in (SELECT movie_id FROM "stars"
join "people" ON stars.person_id=people.id where people.name="Chadwick Boseman" ) ORDER BY ratings.rating DESC LIMIT 5