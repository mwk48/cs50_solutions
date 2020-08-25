SELECT DISTINCT(people.name) from "people"
JOIN "stars" ON people.id=stars.person_id
JOIN "movies" ON movies.id=stars.movie_id where "year" = 2004 GROUP BY people.id ORDER BY people.birth