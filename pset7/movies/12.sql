SELECT distinct(title) FROM "movies"
WHERE "id" IN (select id from "movies" JOIN "stars" ON movies.id=stars.movie_id where stars.movie_id in (SELECT movie_id FROM "stars"
join "people" ON stars.person_id=people.id where people.name="Johnny Depp" ))
AND "id" IN (select id from "movies" JOIN "stars" ON movies.id=stars.movie_id where stars.movie_id in (SELECT movie_id FROM "stars"
join "people" ON stars.person_id=people.id where people.name="Helena Bonham Carter" ))