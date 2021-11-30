-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

--     Your query should output a table with a single column for the name of each person.
--     There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--     Kevin Bacon himself should not be included in the resulting list.

SELECT name FROM people WHERE name != "Kevin Bacon" AND id IN ( -- Do not show Kevin Bacon but show all other names from the people's table with that id
    SELECT DISTINCT person_id FROM stars WHERE movie_id IN ( -- Find the DISTINCT person_id's from the star's table where Kevin Bacon is also a star
    SELECT movie_id FROM stars WHERE person_id IN( --Find movie_id's from the stars table that has the person_id of Kevin Bacon
    SELECT id FROM people WHERE name LIKE "kevin bacon" AND birth = 1958))); --Find Kevin Bacon