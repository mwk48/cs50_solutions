SELECT DISTINCT(people.name) from "people"
JOIN "directors" ON people.id=directors.person_id
JOIN "ratings" ON directors.movie_id=ratings.movie_id where ratings.rating >= 9.0