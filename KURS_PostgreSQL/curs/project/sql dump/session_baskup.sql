--
-- PostgreSQL database dump
--

-- Dumped from database version 13.3 (Ubuntu 13.3-1.pgdg18.04+1)
-- Dumped by pg_dump version 13.3 (Ubuntu 13.3-1.pgdg18.04+1)

-- Started on 2021-06-25 10:30:06 +04

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 3118 (class 1262 OID 20584)
-- Name: session; Type: DATABASE; Schema: -; Owner: ses
--

CREATE DATABASE session WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE = 'ru_RU.UTF-8';


ALTER DATABASE session OWNER TO ses;

\connect session

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 238 (class 1255 OID 21183)
-- Name: add_exam_to_plan(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.add_exam_to_plan() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	stud integer[];
BEGIN
	stud := array(SELECT "idстудент" FROM "студент" WHERE "idгруппа" = new."idгруппа" AND "действующий" = true);
	INSERT INTO "экзамен" ("idуч_план", "idстудент")
		SELECT new."idуч_план", stud[id] from generate_series(1, array_length(stud, 1)) as id;
	RETURN new;
END;
$$;


ALTER FUNCTION public.add_exam_to_plan() OWNER TO ses;

--
-- TOC entry 213 (class 1255 OID 20921)
-- Name: add_student_to_group(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.add_student_to_group() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	UPDATE "группа" SET "кол_во_чел" = "кол_во_чел"+1 WHERE "idгруппа" = new."idгруппа";
	RETURN new;
END;
$$;


ALTER FUNCTION public.add_student_to_group() OWNER TO ses;

--
-- TOC entry 254 (class 1255 OID 21622)
-- Name: change_discipline(integer, text, text, text); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.change_discipline(id_dis integer, name text, inst text, kaf text) RETURNS TABLE("idдисциплина" integer, "название" text, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
DECLARE
	pred record;
	pred2 record;
	opis jsonb;
BEGIN
	opis := (select ('{"институт": "' || inst || '", "кафедра": "' || kaf || '"}')::jsonb);
	
	select * INTO pred FROM "дисциплина" dis WHERE dis."idдисциплина" = id_dis;
	select * INTO pred2 FROM "дисциплина" dis WHERE dis."название" = name AND dis."описание" = opis;
	IF (pred."idдисциплина" is NULL) THEN -- проверка на изменение
		IF (pred2."idдисциплина" is NULL) THEN
			INSERT INTO "дисциплина" ("название", "описание") VALUES (name, opis);
			RETURN QUERY (select dis."idдисциплина", dis."название",
						  dis."описание"->'институт', dis."описание"->'кафедра'
						  from "дисциплина" dis order by dis."idдисциплина" desc limit 1);
		ELSEIF (pred2."действующий") THEN
			RAISE EXCEPTION 'Такая дисциплина уже существует.';
		ELSE
			UPDATE "дисциплина" dis SET "действующий" = true WHERE dis."idдисциплина" = pred2."idдисциплина";
			RETURN QUERY (select dis."idдисциплина", dis."название",
						  dis."описание"->'институт', dis."описание"->'кафедра'
						  from "дисциплина" dis where dis."idдисциплина" = pred2."idдисциплина");
		END IF;
	ELSEIF (pred."действующий") THEN
		IF (pred2."idдисциплина" is NULL) THEN
			IF (opis = (select pr."описание" from "преподаватель" pr where pr."idпреподаватель"
					= (select pl."idпреподаватель" from "уч_план" pl where pl."idдисциплина" = pred."idдисциплина" AND now() < pl."дата_экзамена" limit 1))) THEN
				UPDATE "дисциплина" dis SET "название" = name, "описание" = opis WHERE dis."idдисциплина" = pred."idдисциплина";
				RETURN QUERY (select dis."idдисциплина", dis."название",
						  		dis."описание"->'институт', dis."описание"->'кафедра'
							  from "дисциплина" dis where dis."idдисциплина" = pred."idдисциплина");
			ELSE
				RAISE EXCEPTION 'Вы пытаетесь изменить дисциплину, но у нее есть действующий учебный план с несоответствующими изменению преподавателем.';
			END IF;
		ELSEIF (pred2."действующий") THEN
			RAISE EXCEPTION 'Такая дисциплина уже существует.';
		ELSE
			RAISE EXCEPTION 'Нельзя использовать названия удаленных дисциплин. Вы можете ее востановить';
		END IF;
	ELSE
		RAISE EXCEPTION 'Вы ввели некорректные данные.';
	END IF;
END;
$$;


ALTER FUNCTION public.change_discipline(id_dis integer, name text, inst text, kaf text) OWNER TO ses_admin;

--
-- TOC entry 227 (class 1255 OID 21196)
-- Name: change_exam_of_plan(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.change_exam_of_plan() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	new_l integer;
	old_l integer;
	new_stud integer[];
	old_stud integer[];
	i integer;
BEGIN
	IF (old."idгруппа" <> new."idгруппа") THEN
		new_stud := ARRAY(select "idстудент" from "студент" where "idгруппа" = new."idгруппа");
		new_l := array_length(new_stud, 1);
		old_stud := ARRAY(select "idстудент" from "студент" where "idгруппа" = old."idгруппа");
		old_l := array_length(old_stud, 1);
		
		i := 1;
		WHILE (i <= old_l) LOOP
			DELETE FROM "экзамен" WHERE "idстудент" = old_stud[i] AND "idуч_план" = new."idуч_план";
			i := i+1;
		END LOOP;
		INSERT INTO "экзамен" ("idуч_план", "idстудент")
			SELECT new."idуч_план", new_stud[id] from generate_series(1, new_l) as id;
	END IF;
	
	RETURN new;
END;
$$;


ALTER FUNCTION public.change_exam_of_plan() OWNER TO ses;

--
-- TOC entry 249 (class 1255 OID 21628)
-- Name: change_group(integer, text, text, text); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.change_group(id_gr integer, name text, inst text, kaf text) RETURNS TABLE("idгруппа" integer, "название" text, "кол_во_чел" integer, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
DECLARE
	gr record;
	gr2 record;
	opis jsonb;
BEGIN
	opis := (select ('{"институт": "' || inst || '", "кафедра": "' || kaf || '"}')::jsonb);
	
	select * INTO gr FROM "группа" gru WHERE gru."idгруппа" = id_gr;
	select * INTO gr2 FROM "группа" gru WHERE gru."название" = name AND gru."описание" = opis;
	IF (gr."idгруппа" is NULL) THEN -- проверка на изменение
		IF (gr2."idгруппа" is NULL) THEN
			INSERT INTO "группа" ("название", "описание") VALUES (name, opis);
			RETURN QUERY (select gru."idгруппа", gru."название",
						  gru."кол_во_чел", gru."описание"->'институт', gru."описание"->'кафедра'
						  from "группа" gru order by gru."idгруппа" desc limit 1);
		ELSEIF (gr2."действующий") THEN
			RAISE EXCEPTION 'Такая группа уже существует.';
		ELSE
			UPDATE "группа" gru SET "действующий" = true WHERE gru."idгруппа" = gr2."idгруппа";
			RETURN QUERY (select gru."idгруппа", gru."название",
						  gru."кол_во_чел", gru."описание"->'институт', gru."описание"->'кафедра'
						  from "группа" gru where gru."idгруппа" = gr2."idгруппа");
		END IF;
	ELSEIF (gr."действующий") THEN
		IF (gr2."idгруппа" is NULL) THEN
			UPDATE "группа" gru SET "название" = name, "описание" = opis WHERE gru."idгруппа" = gr."idгруппа";
			RETURN QUERY (select gru."idгруппа", gru."название",
						  gru."кол_во_чел", gru."описание"->'институт', gru."описание"->'кафедра'
						  from "группа" gru where gru."idгруппа" = gr."idгруппа");
		ELSEIF (gr2."действующий") THEN
			RAISE EXCEPTION 'Такая дисциплина уже существует.';
		ELSE
			RAISE EXCEPTION 'Нельзя использовать названия удаленных групп. Вы можете ее востановить';
		END IF;
	ELSE
		RAISE EXCEPTION 'Вы ввели некоректные данные.';
	END IF;
END;
$$;


ALTER FUNCTION public.change_group(id_gr integer, name text, inst text, kaf text) OWNER TO ses_admin;

--
-- TOC entry 256 (class 1255 OID 21270)
-- Name: change_plan(integer, integer, integer, integer, date); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.change_plan(id_plan integer, id_dis integer, id_prep integer, id_gr integer, ex_date date) RETURNS TABLE("idуч_план" integer, "idдисциплина" integer, "idгруппа" integer, "idпреподаватель" integer, "дата_экзамена" text)
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF ((select pl."idуч_план" from "уч_план" pl WHERE pl."idуч_план" = id_plan limit 1) is NULL) THEN
		IF ((select pl."idуч_план" from "уч_план" pl where pl."idдисциплина" = id_dis
					and pl."idпреподаватель" = id_prep
					and pl."idгруппа" = id_gr
			 		and now() < pl."дата_экзамена" limit 1) IS NULL) THEN
			INSERT INTO "уч_план" ("idдисциплина", "idгруппа", "idпреподаватель", "дата_экзамена")
				VALUES (id_dis, id_gr, id_prep, ex_date);
			RETURN QUERY (select  pl."idуч_план", pl."idдисциплина", pl."idгруппа", pl."idпреподаватель", to_char(pl."дата_экзамена",'YYYY-MM-DD')
						  from "уч_план" pl order by pl."idуч_план" desc limit 1);
		ELSE
			RAISE EXCEPTION 'Такой учебный план уже существует.';
		END IF;
	ELSE
		UPDATE "уч_план" pl SET "idдисциплина" = id_dis, "idгруппа" = id_gr, "idпреподаватель" = id_prep, "дата_экзамена" = ex_date
			WHERE pl."idуч_план" = id_plan;
		RETURN QUERY (select  pl."idуч_план", pl."idдисциплина", pl."idгруппа", pl."idпреподаватель", to_char(pl."дата_экзамена",'YYYY-MM-DD')
					  from "уч_план" pl where pl."idуч_план" = id_plan);
	END IF;
END;
$$;


ALTER FUNCTION public.change_plan(id_plan integer, id_dis integer, id_prep integer, id_gr integer, ex_date date) OWNER TO ses_admin;

--
-- TOC entry 250 (class 1255 OID 21336)
-- Name: change_student(integer, integer, text, text, integer); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.change_student(id_stud integer, new_id integer, fio text, pas text, id_gr integer) RETURNS TABLE("idстарая_группа" integer, "idновая_группа" integer, "idстарая_группа_кол" integer, "idновая_группа_кол" integer, "idстудент" integer, "ФИО" text, "пароль" text)
    LANGUAGE plpgsql
    AS $$
DECLARE
	old_id_gr integer;
	old_gr_kol integer;
	new_gr_kol integer;
	stud record;
BEGIN
	old_id_gr := (select st."idгруппа" from "студент" st where st."idстудент" = id_stud);

	IF ((select gr."idгруппа" from "группа" gr where gr."idгруппа" = id_gr)) THEN
		IF (id_stud <> new_id) THEN
			select * INTO stud from "студент" st where st."idстудент" = new_id;
			IF (stud."idстудент" is NULL) THEN
				INSERT INTO public."студент" ("idстудент", "ФИО", "пароль", "idгруппа")
					VALUES (new_id, fio, pas, id_gr);


				old_gr_kol := (select gr."кол_во_чел" from "группа" gr where gr."idгруппа" = old_id_gr);
				new_gr_kol := (select gr."кол_во_чел" from "группа" gr where gr."idгруппа" = id_gr);
				RETURN QUERY (select old_id_gr, id_gr, old_gr_kol, new_gr_kol, st."idстудент", st."ФИО", st."пароль"
							  from "студент" st where st."idстудент" = new_id);
			ELSEIF (stud."действующий") THEN
				RAISE EXCEPTION 'Ученик с таким id уже существует.';
			ELSE
				RAISE EXCEPTION 'Ученик с таким id уже существовал.';
			END IF;
		ELSE
			select * INTO stud from "студент" st where st."idстудент" = id_stud;
			IF (stud."idстудент" is NULL) THEN
				RAISE EXCEPTION 'Введены некорректные данные.';
			ELSEIF (stud."действующий") THEN
				UPDATE "студент" st
				SET "ФИО" = fio, "пароль" = pas, "idгруппа" = id_gr
				WHERE st."idстудент" = stud."idстудент";


				old_gr_kol := (select gr."кол_во_чел" from "группа" gr where gr."idгруппа" = old_id_gr);
				new_gr_kol := (select gr."кол_во_чел" from "группа" gr where gr."idгруппа" = id_gr);
				RETURN QUERY (select old_id_gr, id_gr, old_gr_kol, new_gr_kol, st."idстудент", st."ФИО", st."пароль"
							  from "студент" st where st."idстудент" = stud."idстудент");
			ELSE
				RAISE EXCEPTION 'Нельзя изменять данные существовавших учеников.';
			END IF;
		END IF;
	ELSE
		RAISE EXCEPTION 'Такая группа не существует.';
	END IF;
END;
$$;


ALTER FUNCTION public.change_student(id_stud integer, new_id integer, fio text, pas text, id_gr integer) OWNER TO ses_admin;

--
-- TOC entry 251 (class 1255 OID 21620)
-- Name: change_teacher(integer, integer, text, text, text, text); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.change_teacher(id_prep integer, new_id integer, fio text, pas text, inst text, kaf text) RETURNS TABLE("idпреподаватель" integer, "ФИО" text, "пароль" text, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
DECLARE
	prep record;
	opis jsonb;
BEGIN
	opis := (select ('{"институт": "' || inst || '", "кафедра": "' || kaf || '"}')::jsonb);
	IF (id_prep <> new_id) THEN
		select * INTO prep from "преподаватель" pr where pr."idпреподаватель" = new_id;
		IF (prep."idпреподаватель" is NULL) THEN
			INSERT INTO "преподаватель" ("idпреподаватель", "ФИО", "пароль", "описание") VALUES (new_id, fio, pas, opis);
			RETURN QUERY (select pr."idпреподаватель", pr."ФИО", pr."пароль",
						  pr."описание"->'институт', pr."описание"->'кафедра'
						  from "преподаватель" pr where pr."idпреподаватель" = new_id);
		ELSEIF (prep."действующий") THEN
			RAISE EXCEPTION 'Преподаватель с таким id уже существует.';
		ELSE
			RAISE EXCEPTION 'Преподаватель с таким id уже существовал.';
		END IF;
	ELSE
		select * INTO prep from "преподаватель" pr where pr."idпреподаватель" = id_prep;
		IF (prep."idпреподаватель" is NULL) THEN
			RAISE EXCEPTION 'Введены некорректные данные.';
		ELSEIF (prep."действующий") THEN
			IF (opis = (select dis."описание" from "дисциплина" dis where dis."idдисциплина"
					= (select pl."idдисциплина" from "уч_план" pl where pl."idпреподаватель" = prep."idпреподаватель" AND now() < pl."дата_экзамена" limit 1))) THEN
				UPDATE "преподаватель" pr
				SET "ФИО" = fio, "пароль" = pas, "описание" = opis
				WHERE pr."idпреподаватель" = prep."idпреподаватель";
				RETURN QUERY (select pr."idпреподаватель", pr."ФИО", pr."пароль",
						  		pr."описание"->'институт', pr."описание"->'кафедра'
							  from "преподаватель" pr where pr."idпреподаватель" = prep."idпреподаватель");
			ELSE
				RAISE EXCEPTION 'Вы пытаетесь перевести преподавателя, но у него есть действующий учебный план с несоответствующими переводу дисциплинами.';
			END IF;
		ELSE
			RAISE EXCEPTION 'Нельзя изменять данные существовавших преподавателей.';
		END IF;
	END IF;
END;
$$;


ALTER FUNCTION public.change_teacher(id_prep integer, new_id integer, fio text, pas text, inst text, kaf text) OWNER TO ses_admin;

--
-- TOC entry 255 (class 1255 OID 21185)
-- Name: check_data_for_plan(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_data_for_plan() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	dis record;
	prep record;
	gr record;
BEGIN
	select "действующий", "описание" into dis from "дисциплина" where "idдисциплина" = new."idдисциплина";
	select "действующий", "описание" into prep from "преподаватель" where "idпреподаватель" = new."idпреподаватель";
	select "действующий" into gr from "группа" where "idгруппа" = new."idгруппа";
	
	IF (dis."действующий" is NULL) THEN
		RAISE EXCEPTION 'Вы пытаетесь ввести недействительную дисциплину.';
	ELSEIF (prep."действующий" is NULL) THEN
		RAISE EXCEPTION 'Вы пытаетесь ввести недействительного преподавателя.';
	ELSEIF (gr."действующий" is NULL) THEN
		RAISE EXCEPTION 'Вы пытаетесь ввести недействительная группа.';
	ELSEIF (dis."описание" <> prep."описание") THEN
		RAISE EXCEPTION 'Вы пытаетесь поставить преподавателем на дисциплину, человека из другой сферы.';
	END IF;
	RETURN new;
END;
$$;


ALTER FUNCTION public.check_data_for_plan() OWNER TO ses;

--
-- TOC entry 244 (class 1255 OID 21191)
-- Name: check_date_of_plan_ex(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_date_of_plan_ex() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (now() >= new."дата_экзамена") THEN
		RAISE EXCEPTION 'Нельзя изменять уч_план во время и после Даты Экзамена.';
	END IF;
	RETURN new;
END;
$$;


ALTER FUNCTION public.check_date_of_plan_ex() OWNER TO ses;

--
-- TOC entry 235 (class 1255 OID 21217)
-- Name: check_remove_discipline(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_remove_discipline() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (old."действующий" = true and new."действующий" = false) THEN
		IF ((select "idуч_план" from "уч_план" where "idдисциплина" = new."idдисциплина" limit 1) IS NOT NULL) THEN
			RAISE EXCEPTION 'Вы пытаетесь удалить дисциплину, которая использована в уч плане.';
		END IF;
	END IF;
	RETURN new;
END;
$$;


ALTER FUNCTION public.check_remove_discipline() OWNER TO ses;

--
-- TOC entry 240 (class 1255 OID 21223)
-- Name: check_remove_group(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_remove_group() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	dis boolean;
	plan boolean;
BEGIN
	IF (old."действующий" = true and new."действующий" = false) THEN
		IF ((select "idуч_план" from "уч_план" where "idгруппа" = new."idгруппа" limit 1) IS NOT NULL) THEN
			RAISE EXCEPTION 'Вы пытаетесь удалить группу, которая назначена в уч плане.';
		END IF;
		IF ((select "кол_во_чел" from "группа" where "idгруппа" = new."idгруппа") > 0) THEN
			RAISE EXCEPTION 'Вы пытаетесь удалить группу, в которой есть студенты.';
		END IF;
	END IF;
	RETURN new;
END;
$$;


ALTER FUNCTION public.check_remove_group() OWNER TO ses;

--
-- TOC entry 237 (class 1255 OID 21227)
-- Name: check_remove_plan(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_remove_plan() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	dis boolean;
	plan boolean;
BEGIN
	IF (now() >= old."дата_экзамена") THEN
		RAISE EXCEPTION 'Нельзя изменять уч_план во время и после Даты Экзамена.';
	END IF;
	RETURN old;
END;
$$;


ALTER FUNCTION public.check_remove_plan() OWNER TO ses;

--
-- TOC entry 236 (class 1255 OID 21220)
-- Name: check_remove_teacher(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.check_remove_teacher() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (old."действующий" = true and new."действующий" = false) THEN
		IF ((select "idуч_план" from "уч_план" where "idпреподаватель" = new."idпреподаватель" limit 1) IS NOT NULL) THEN
			RAISE EXCEPTION 'Вы пытаетесь удалить преподавателя, которой назначен в уч плане.';
		END IF;
	END IF;
	RETURN new;
END;
$$;


ALTER FUNCTION public.check_remove_teacher() OWNER TO ses;

--
-- TOC entry 228 (class 1255 OID 21181)
-- Name: check_student(integer, text); Type: FUNCTION; Schema: public; Owner: ses_user
--

CREATE FUNCTION public.check_student(id integer, pas text) RETURNS boolean
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN ((select idстудент
			from студент 
			where idстудент = id
				and пароль = pas) is not NULL);
END;
$$;


ALTER FUNCTION public.check_student(id integer, pas text) OWNER TO ses_user;

--
-- TOC entry 230 (class 1255 OID 21182)
-- Name: check_teacher(integer, text); Type: FUNCTION; Schema: public; Owner: ses_user
--

CREATE FUNCTION public.check_teacher(id integer, pas text) RETURNS boolean
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN ((select idпреподаватель
			from преподаватель 
			where idпреподаватель = id
				and пароль = pas) is not NULL);
END;
$$;


ALTER FUNCTION public.check_teacher(id integer, pas text) OWNER TO ses_user;

--
-- TOC entry 225 (class 1255 OID 20985)
-- Name: create_data(); Type: PROCEDURE; Schema: public; Owner: ses
--

CREATE PROCEDURE public.create_data()
    LANGUAGE plpgsql
    AS $$
DECLARE
	i integer;
	dats date[];
	ex_data date;
	min_plan integer;
	max_plan integer;
	id_gr integer;
BEGIN
	delete from "экзамен";
	delete from "оценка";
	delete from "уч_план";
	delete from "студент";
	delete from "группа";
	delete from "дисциплина";
	delete from "преподаватель";

	insert into "группа" ("idгруппа", "название")
		select id,
			md5(random()::text)
		from generate_series(1,4) as id;

	insert into "студент" ("idстудент", "ФИО", "idгруппа")
		select id,
			md5(random()::text),
			(random()*3+1)::integer
		from generate_series(1,36) as id;

	insert into "преподаватель" ("idпреподаватель", "ФИО")
		select id,
			md5(random()::text)
		from generate_series(1,2) as id;

	insert into "дисциплина" ("idдисциплина", "название")
		select id,
			md5(random()::text)
		from generate_series(1,2) as id;
	
	i := 1;
	while (i <= 4) loop
		insert into "уч_план" ("idдисциплина", "idпреподаватель", "idгруппа", "дата_экзамена")
			select "idдисциплина", (random()+1)::integer, i, (now() + INTERVAL '1 day' * ((random()*100)::integer))
			from "дисциплина";
		i := i+1;
	end loop;

	insert into "оценка" ("idоценка", "название")
		values (1, 'отлично'), (2, 'хорошо'), (3, 'удавлетворительно'), (4, 'пересдача');
		
		
	min_plan := (select min("idуч_план") from "уч_план");
	max_plan := (select max("idуч_план") from "уч_план");
	while (min_plan <= max_plan) loop
		ex_data := (select "дата_экзамена" from "уч_план" where "idуч_план" = min_plan);
		dats := array_append(array(select (ex_data + INTERVAL '1 day' * ((random()*100)::integer))::date from generate_series(1, (random()*2)::integer)), ex_data);
		id_gr := (select "idгруппа" from "уч_план" where "idуч_план" = min_plan);
		insert into "экзамен" ("idуч_план", "idстудент", "idоценка", "даты_сдачи")
			select min_plan,
				"idстудент",
				(random()*3+1)::integer,
				dats
			from "студент" where "idгруппа" = id_gr;
		min_plan := min_plan + 1;
	end loop;
END;
$$;


ALTER PROCEDURE public.create_data() OWNER TO ses;

--
-- TOC entry 229 (class 1255 OID 21293)
-- Name: delete_data(); Type: PROCEDURE; Schema: public; Owner: ses
--

CREATE PROCEDURE public.delete_data()
    LANGUAGE plpgsql
    AS $$
BEGIN
	delete from "экзамен";
	delete from "уч_план";
	delete from "студент";
	delete from "группа";
	delete from "дисциплина";
	delete from "преподаватель";
	
	alter sequence экзамен_idэкзамен_seq restart;
	alter sequence уч_план_idуч_план_seq restart;
	alter sequence группа_idгруппа_seq restart;
	alter sequence дисциплина_idдисциплина_seq restart;
END;
$$;


ALTER PROCEDURE public.delete_data() OWNER TO ses;

--
-- TOC entry 248 (class 1255 OID 21317)
-- Name: get_discipline(); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.get_discipline() RETURNS TABLE("idдисциплина" integer, "название" text, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN QUERY (select dis."idдисциплина", dis."название", dis."описание"->'институт', dis."описание"->'кафедра' from "дисциплина" dis where dis."действующий" = true);
END;
$$;


ALTER FUNCTION public.get_discipline() OWNER TO ses_admin;

--
-- TOC entry 234 (class 1255 OID 21320)
-- Name: get_group(); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.get_group() RETURNS TABLE("idгруппа" integer, "название" text, "кол_во_чел" integer, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN QUERY (select gr."idгруппа", gr."название", gr."кол_во_чел", gr."описание"->'институт', gr."описание"->'кафедра' from "группа" gr where gr."действующий" = true);
END;
$$;


ALTER FUNCTION public.get_group() OWNER TO ses_admin;

--
-- TOC entry 226 (class 1255 OID 21257)
-- Name: get_plan(); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.get_plan() RETURNS TABLE("idуч_план" integer, "idдисциплина" integer, "idгруппа" integer, "idпреподаватель" integer, "дата_экзамена" text)
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN QUERY (select pl."idуч_план", pl."idдисциплина", pl."idгруппа", pl."idпреподаватель", to_char(pl."дата_экзамена",'YYYY-MM-DD')
				  from "уч_план" pl where now() < pl."дата_экзамена");
END;
$$;


ALTER FUNCTION public.get_plan() OWNER TO ses_admin;

--
-- TOC entry 245 (class 1255 OID 21260)
-- Name: get_plan_stud(integer); Type: FUNCTION; Schema: public; Owner: ses_prep
--

CREATE FUNCTION public.get_plan_stud(id_plan integer) RETURNS TABLE("idстудент" integer, "ФИО" text, "idоценка" integer, "даты_сдачи" text[], "можно_сдавать" boolean)
    LANGUAGE plpgsql
    AS $$
DECLARE
	dates_string text[];
	exams record;
BEGIN
	for exams in (select ex."idэкзамен", ex."idстудент", ex."idоценка", ex."даты_сдачи" from "экзамен" ex where ex."idуч_план" = id_plan) loop
		dates_string := array(select to_char(date_str,'YYYY-MM-DD') from unnest(exams."даты_сдачи") as date_str);
		
		RETURN QUERY (select exams."idстудент", (select st."ФИО" from "студент" st where st."idстудент" = exams."idстудент"),
					  	exams."idоценка", dates_string, (array_length(exams."даты_сдачи", 1) < 3));
	end loop;
END;
$$;


ALTER FUNCTION public.get_plan_stud(id_plan integer) OWNER TO ses_prep;

--
-- TOC entry 253 (class 1255 OID 21635)
-- Name: get_stud_ex(integer); Type: FUNCTION; Schema: public; Owner: ses_stud
--

CREATE FUNCTION public.get_stud_ex(id_stud integer) RETURNS TABLE("название_дисциплина" text, "описание_дисциплина" jsonb, "ФИО_преподаватель" text, "описание_преподаватель" jsonb, "дата_экзамена" text, "оценка" text, "даты_сдачи" text[])
    LANGUAGE plpgsql
    AS $$
DECLARE
	plan_info record;
	date_string text[];
	ids_plan_of_discipline record;
	dis record;
	prep record;
BEGIN
	for ids_plan_of_discipline in (select ex."idуч_план", ex."idоценка", ex."даты_сдачи" from "экзамен" as ex where "idстудент" = id_stud) loop
		date_string := array(select to_char(date_str,'YYYY-MM-DD') from unnest(ids_plan_of_discipline."даты_сдачи") as date_str);
		
		select pl."дата_экзамена", pl."idдисциплина", pl."idпреподаватель" into plan_info
			from "уч_план" pl where pl."idуч_план" = ids_plan_of_discipline."idуч_план";
		
		select "название", "описание" into dis from "дисциплина" where "idдисциплина" = plan_info."idдисциплина";
		select "ФИО", "описание" into prep from "преподаватель" where "idпреподаватель" = plan_info."idпреподаватель";
		RETURN QUERY (select dis."название", dis."описание",
					  prep."ФИО", prep."описание", to_char(plan_info."дата_экзамена",'YYYY-MM-DD'),
					  (select "название" from "оценка" where "idоценка" = ids_plan_of_discipline."idоценка"), date_string);
	end loop;
END;
$$;


ALTER FUNCTION public.get_stud_ex(id_stud integer) OWNER TO ses_stud;

--
-- TOC entry 231 (class 1255 OID 21604)
-- Name: get_student(); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.get_student() RETURNS TABLE("idстудент" integer, "ФИО" text, "idгруппа" integer, "пароль" text)
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN QUERY (select st."idстудент", st."ФИО", st."idгруппа", st."пароль"
				  from "студент" st where st."действующий" = true);
END;
$$;


ALTER FUNCTION public.get_student() OWNER TO ses_admin;

--
-- TOC entry 241 (class 1255 OID 21321)
-- Name: get_teacher(); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.get_teacher() RETURNS TABLE("idпреподаватель" integer, "ФИО" text, "пароль" text, "институт" jsonb, "кафедра" jsonb)
    LANGUAGE plpgsql
    AS $$
BEGIN
	RETURN QUERY (select pr."idпреподаватель", pr."ФИО", pr."пароль", pr."описание"->'институт', pr."описание"->'кафедра' from "преподаватель" pr where pr."действующий" = true);
END;
$$;


ALTER FUNCTION public.get_teacher() OWNER TO ses_admin;

--
-- TOC entry 252 (class 1255 OID 21633)
-- Name: get_teacher_plan(integer); Type: FUNCTION; Schema: public; Owner: ses_prep
--

CREATE FUNCTION public.get_teacher_plan(id_prep integer) RETURNS TABLE("idуч_план" integer, "idдисциплина" integer, "название_дисциплина" text, "описание_дисциплина" jsonb, "idгруппа" integer, "название_группа" text, "описание_группа" jsonb, "дата_экзамена" text)
    LANGUAGE plpgsql
    AS $$
DECLARE
	plan record;
	grup record;
	disc record;
BEGIN
	for plan in (select * from "уч_план" pl where pl."idпреподаватель" = id_prep) loop
		select gr."название", gr."описание" into grup from "группа" gr where gr."idгруппа" = plan."idгруппа";
		select dis."название", dis."описание" into disc from "дисциплина" dis where dis."idдисциплина" = plan."idдисциплина";
		RETURN QUERY (select plan."idуч_план", plan."idдисциплина", disc."название", disc."описание",
					  plan."idгруппа", grup."название", grup."описание", to_char(plan."дата_экзамена",'YYYY-MM-DD'));
	end loop;
END;
$$;


ALTER FUNCTION public.get_teacher_plan(id_prep integer) OWNER TO ses_prep;

--
-- TOC entry 232 (class 1255 OID 21216)
-- Name: remove_discipline(integer); Type: PROCEDURE; Schema: public; Owner: ses_admin
--

CREATE PROCEDURE public.remove_discipline(id_dis integer)
    LANGUAGE plpgsql
    AS $$
BEGIN
	UPDATE "дисциплина" SET "действующий" = false WHERE "idдисциплина" = id_dis;
END;
$$;


ALTER PROCEDURE public.remove_discipline(id_dis integer) OWNER TO ses_admin;

--
-- TOC entry 247 (class 1255 OID 21265)
-- Name: remove_exam(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.remove_exam() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM "экзамен" WHERE "idуч_план" = old."idуч_план";
	RETURN old;
END;
$$;


ALTER FUNCTION public.remove_exam() OWNER TO ses;

--
-- TOC entry 212 (class 1255 OID 21225)
-- Name: remove_group(integer); Type: PROCEDURE; Schema: public; Owner: ses_admin
--

CREATE PROCEDURE public.remove_group(id_gr integer)
    LANGUAGE plpgsql
    AS $$
BEGIN
	UPDATE "группа" SET "действующий" = false WHERE "idгруппа" = id_gr;
END;
$$;


ALTER PROCEDURE public.remove_group(id_gr integer) OWNER TO ses_admin;

--
-- TOC entry 239 (class 1255 OID 21226)
-- Name: remove_plan(integer); Type: PROCEDURE; Schema: public; Owner: ses_admin
--

CREATE PROCEDURE public.remove_plan(id_plan integer)
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM "уч_план" WHERE "idуч_план" = id_plan;
END;
$$;


ALTER PROCEDURE public.remove_plan(id_plan integer) OWNER TO ses_admin;

--
-- TOC entry 242 (class 1255 OID 21240)
-- Name: remove_student(integer); Type: FUNCTION; Schema: public; Owner: ses_admin
--

CREATE FUNCTION public.remove_student(id_stud integer) RETURNS TABLE("idгруппа" integer, "кол_во_чел" integer)
    LANGUAGE plpgsql
    AS $$
DECLARE
	id_gr integer;
BEGIN
	UPDATE "студент" SET "действующий" = false WHERE "idстудент" = id_stud;
	id_gr := (select st."idгруппа" from "студент" st where st."idстудент" = id_stud);
	
	RETURN QUERY (select gr."idгруппа", gr."кол_во_чел" from "группа" gr where gr."idгруппа" = id_gr);
END;
$$;


ALTER FUNCTION public.remove_student(id_stud integer) OWNER TO ses_admin;

--
-- TOC entry 233 (class 1255 OID 21219)
-- Name: remove_teacher(integer); Type: PROCEDURE; Schema: public; Owner: ses_admin
--

CREATE PROCEDURE public.remove_teacher(id_prep integer)
    LANGUAGE plpgsql
    AS $$
BEGIN
	UPDATE "преподаватель" SET "действующий" = false WHERE "idпреподаватель" = id_prep;
END;
$$;


ALTER PROCEDURE public.remove_teacher(id_prep integer) OWNER TO ses_admin;

--
-- TOC entry 246 (class 1255 OID 21264)
-- Name: save_change_exam(integer, integer, integer); Type: FUNCTION; Schema: public; Owner: ses_prep
--

CREATE FUNCTION public.save_change_exam(id_stud integer, id_plan integer, id_rat integer) RETURNS TABLE("дата_сдачи" text, "можно_сдавать" boolean)
    LANGUAGE plpgsql
    AS $$
DECLARE
	now_date date;
BEGIN
	now_date := now()::date;
	UPDATE "экзамен" SET "idоценка" = id_rat, "даты_сдачи" = array_append("даты_сдачи", now_date)
		WHERE "idуч_план" = id_plan AND "idстудент" = id_stud;
	
	RETURN QUERY (select to_char(now_date,'YYYY-MM-DD'), (array_length("даты_сдачи", 1) < 3) from "экзамен" where "idуч_план" = id_plan AND "idстудент" = id_stud);
END;
$$;


ALTER FUNCTION public.save_change_exam(id_stud integer, id_plan integer, id_rat integer) OWNER TO ses_prep;

--
-- TOC entry 243 (class 1255 OID 21179)
-- Name: student_update(); Type: FUNCTION; Schema: public; Owner: ses
--

CREATE FUNCTION public.student_update() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (old."действующий" = true AND new."действующий" = false) THEN -- удалили студента
		
		UPDATE "группа" SET "кол_во_чел" = "кол_во_чел"-1 WHERE "idгруппа" = old."idгруппа";
		DELETE FROM "экзамен" WHERE "idстудент" = old."idстудент" AND "idуч_план" IN
			(select "idуч_план" FROM "уч_план" WHERE "idгруппа" = old."idгруппа" and now() < "дата_экзамена");
	ELSEIF (old."действующий" = false AND new."действующий" = true) THEN -- восстановили студента
		
		UPDATE "группа" SET "кол_во_чел" = "кол_во_чел"+1 WHERE "idгруппа" = new."idгруппа";
		INSERT INTO "экзамен" ("idстудент", "idуч_план")
			select new."idстудент", "idуч_план" FROM "уч_план" WHERE "idгруппа" = old."idгруппа" and now() < "дата_экзамена";
	ELSEIF (old."действующий" = true AND new."действующий" = true) THEN -- Другие измения
		
		IF (old."idгруппа" <> new."idгруппа") THEN
			UPDATE "группа" SET "кол_во_чел" = "кол_во_чел"+1 WHERE "idгруппа" = new."idгруппа";
			UPDATE "группа" SET "кол_во_чел" = "кол_во_чел"-1 WHERE "idгруппа" = old."idгруппа";
			
			DELETE FROM "экзамен" ex WHERE ex."idстудент" = old."idстудент" AND ex."idуч_план" IN
				(select pl."idуч_план" FROM "уч_план" pl WHERE pl."idгруппа" = old."idгруппа" and now() < "дата_экзамена");
				
			INSERT INTO "экзамен" ("idстудент", "idуч_план")
				select new."idстудент", pl."idуч_план" FROM "уч_план" pl WHERE pl."idгруппа" = new."idгруппа" and now() < "дата_экзамена";
		END IF;
	END IF;
	
	RETURN new;
END;
$$;


ALTER FUNCTION public.student_update() OWNER TO ses;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 205 (class 1259 OID 20740)
-- Name: группа; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."группа" (
    "idгруппа" integer NOT NULL,
    "название" text NOT NULL,
    "кол_во_чел" integer DEFAULT 0 NOT NULL,
    "действующий" boolean DEFAULT true NOT NULL,
    "описание" jsonb NOT NULL
);


ALTER TABLE public."группа" OWNER TO ses;

--
-- TOC entry 204 (class 1259 OID 20738)
-- Name: группа_idгруппа_seq; Type: SEQUENCE; Schema: public; Owner: ses
--

CREATE SEQUENCE public."группа_idгруппа_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."группа_idгруппа_seq" OWNER TO ses;

--
-- TOC entry 3120 (class 0 OID 0)
-- Dependencies: 204
-- Name: группа_idгруппа_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: ses
--

ALTER SEQUENCE public."группа_idгруппа_seq" OWNED BY public."группа"."idгруппа";


--
-- TOC entry 203 (class 1259 OID 20724)
-- Name: дисциплина; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."дисциплина" (
    "idдисциплина" integer NOT NULL,
    "название" text NOT NULL,
    "действующий" boolean DEFAULT true NOT NULL,
    "описание" jsonb NOT NULL
);


ALTER TABLE public."дисциплина" OWNER TO ses;

--
-- TOC entry 202 (class 1259 OID 20722)
-- Name: дисциплина_idдисциплина_seq; Type: SEQUENCE; Schema: public; Owner: ses
--

CREATE SEQUENCE public."дисциплина_idдисциплина_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."дисциплина_idдисциплина_seq" OWNER TO ses;

--
-- TOC entry 3122 (class 0 OID 0)
-- Dependencies: 202
-- Name: дисциплина_idдисциплина_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: ses
--

ALTER SEQUENCE public."дисциплина_idдисциплина_seq" OWNED BY public."дисциплина"."idдисциплина";


--
-- TOC entry 201 (class 1259 OID 20691)
-- Name: оценка; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."оценка" (
    "idоценка" integer NOT NULL,
    "название" text NOT NULL
);


ALTER TABLE public."оценка" OWNER TO ses;

--
-- TOC entry 200 (class 1259 OID 20689)
-- Name: оценка_idоценка_seq; Type: SEQUENCE; Schema: public; Owner: ses
--

CREATE SEQUENCE public."оценка_idоценка_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."оценка_idоценка_seq" OWNER TO ses;

--
-- TOC entry 3124 (class 0 OID 0)
-- Dependencies: 200
-- Name: оценка_idоценка_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: ses
--

ALTER SEQUENCE public."оценка_idоценка_seq" OWNED BY public."оценка"."idоценка";


--
-- TOC entry 209 (class 1259 OID 21143)
-- Name: преподаватель; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."преподаватель" (
    "idпреподаватель" integer NOT NULL,
    "ФИО" text NOT NULL,
    "пароль" text DEFAULT 123 NOT NULL,
    "действующий" boolean DEFAULT true NOT NULL,
    "описание" jsonb NOT NULL
);


ALTER TABLE public."преподаватель" OWNER TO ses;

--
-- TOC entry 208 (class 1259 OID 20882)
-- Name: студент; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."студент" (
    "idстудент" integer NOT NULL,
    "ФИО" text NOT NULL,
    "idгруппа" integer NOT NULL,
    "пароль" text DEFAULT 123 NOT NULL,
    "действующий" boolean DEFAULT true NOT NULL
);


ALTER TABLE public."студент" OWNER TO ses;

--
-- TOC entry 206 (class 1259 OID 20813)
-- Name: уч_план; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."уч_план" (
    "idдисциплина" integer NOT NULL,
    "idгруппа" integer NOT NULL,
    "idуч_план" integer NOT NULL,
    "дата_экзамена" date NOT NULL,
    "idпреподаватель" integer DEFAULT 1 NOT NULL
);


ALTER TABLE public."уч_план" OWNER TO ses;

--
-- TOC entry 207 (class 1259 OID 20835)
-- Name: уч_план_idуч_план_seq; Type: SEQUENCE; Schema: public; Owner: ses
--

CREATE SEQUENCE public."уч_план_idуч_план_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."уч_план_idуч_план_seq" OWNER TO ses;

--
-- TOC entry 3128 (class 0 OID 0)
-- Dependencies: 207
-- Name: уч_план_idуч_план_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: ses
--

ALTER SEQUENCE public."уч_план_idуч_план_seq" OWNED BY public."уч_план"."idуч_план";


--
-- TOC entry 211 (class 1259 OID 21372)
-- Name: экзамен; Type: TABLE; Schema: public; Owner: ses
--

CREATE TABLE public."экзамен" (
    "idэкзамен" integer NOT NULL,
    "idуч_план" integer NOT NULL,
    "idстудент" integer NOT NULL,
    "idоценка" integer,
    "даты_сдачи" date[],
    CONSTRAINT "экзамен_idэкзамен_check" CHECK (("idэкзамен" > 0)),
    CONSTRAINT "экзамен_даты_сдачи_check" CHECK ((array_length("даты_сдачи", 1) < 4))
);


ALTER TABLE public."экзамен" OWNER TO ses;

--
-- TOC entry 210 (class 1259 OID 21370)
-- Name: экзамен_idэкзамен_seq; Type: SEQUENCE; Schema: public; Owner: ses
--

CREATE SEQUENCE public."экзамен_idэкзамен_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."экзамен_idэкзамен_seq" OWNER TO ses;

--
-- TOC entry 3130 (class 0 OID 0)
-- Dependencies: 210
-- Name: экзамен_idэкзамен_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: ses
--

ALTER SEQUENCE public."экзамен_idэкзамен_seq" OWNED BY public."экзамен"."idэкзамен";


--
-- TOC entry 2907 (class 2604 OID 20743)
-- Name: группа idгруппа; Type: DEFAULT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."группа" ALTER COLUMN "idгруппа" SET DEFAULT nextval('public."группа_idгруппа_seq"'::regclass);


--
-- TOC entry 2904 (class 2604 OID 20727)
-- Name: дисциплина idдисциплина; Type: DEFAULT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."дисциплина" ALTER COLUMN "idдисциплина" SET DEFAULT nextval('public."дисциплина_idдисциплина_seq"'::regclass);


--
-- TOC entry 2903 (class 2604 OID 20694)
-- Name: оценка idоценка; Type: DEFAULT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."оценка" ALTER COLUMN "idоценка" SET DEFAULT nextval('public."оценка_idоценка_seq"'::regclass);


--
-- TOC entry 2911 (class 2604 OID 20837)
-- Name: уч_план idуч_план; Type: DEFAULT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план" ALTER COLUMN "idуч_план" SET DEFAULT nextval('public."уч_план_idуч_план_seq"'::regclass);


--
-- TOC entry 2920 (class 2604 OID 21375)
-- Name: экзамен idэкзамен; Type: DEFAULT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен" ALTER COLUMN "idэкзамен" SET DEFAULT nextval('public."экзамен_idэкзамен_seq"'::regclass);


--
-- TOC entry 3106 (class 0 OID 20740)
-- Dependencies: 205
-- Data for Name: группа; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."группа" ("idгруппа", "название", "кол_во_чел", "действующий", "описание") VALUES (1, 'гр1', 1, true, '{"кафедра": "каф1", "институт": "инст1"}');
INSERT INTO public."группа" ("idгруппа", "название", "кол_во_чел", "действующий", "описание") VALUES (2, 'гр2', 1, true, '{"кафедра": "каф2", "институт": "инст2"}');


--
-- TOC entry 3104 (class 0 OID 20724)
-- Dependencies: 203
-- Data for Name: дисциплина; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."дисциплина" ("idдисциплина", "название", "действующий", "описание") VALUES (1, 'дис1', true, '{"кафедра": "каф1", "институт": "инст1"}');
INSERT INTO public."дисциплина" ("idдисциплина", "название", "действующий", "описание") VALUES (2, 'дис2', true, '{"кафедра": "каф2", "институт": "инст2"}');
INSERT INTO public."дисциплина" ("idдисциплина", "название", "действующий", "описание") VALUES (3, 'дис3', true, '{"кафедра": "каф3", "институт": "инст3"}');
INSERT INTO public."дисциплина" ("idдисциплина", "название", "действующий", "описание") VALUES (4, '', true, '{"кафедра": "", "институт": ""}');


--
-- TOC entry 3102 (class 0 OID 20691)
-- Dependencies: 201
-- Data for Name: оценка; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."оценка" ("idоценка", "название") VALUES (1, 'отлично');
INSERT INTO public."оценка" ("idоценка", "название") VALUES (2, 'хорошо');
INSERT INTO public."оценка" ("idоценка", "название") VALUES (3, 'удавлетворительно');
INSERT INTO public."оценка" ("idоценка", "название") VALUES (4, 'пересдача');


--
-- TOC entry 3110 (class 0 OID 21143)
-- Dependencies: 209
-- Data for Name: преподаватель; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."преподаватель" ("idпреподаватель", "ФИО", "пароль", "действующий", "описание") VALUES (123, 'преп1', '123', true, '{"кафедра": "каф1", "институт": "инст1"}');
INSERT INTO public."преподаватель" ("idпреподаватель", "ФИО", "пароль", "действующий", "описание") VALUES (456, 'преп2', '456', true, '{"кафедра": "каф2", "институт": "инст2"}');


--
-- TOC entry 3109 (class 0 OID 20882)
-- Dependencies: 208
-- Data for Name: студент; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."студент" ("idстудент", "ФИО", "idгруппа", "пароль", "действующий") VALUES (123, 'студ1', 1, '123', true);
INSERT INTO public."студент" ("idстудент", "ФИО", "idгруппа", "пароль", "действующий") VALUES (456, 'студ2', 2, '456', true);


--
-- TOC entry 3107 (class 0 OID 20813)
-- Dependencies: 206
-- Data for Name: уч_план; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."уч_план" ("idдисциплина", "idгруппа", "idуч_план", "дата_экзамена", "idпреподаватель") VALUES (1, 1, 5, '2021-12-15', 123);
INSERT INTO public."уч_план" ("idдисциплина", "idгруппа", "idуч_план", "дата_экзамена", "idпреподаватель") VALUES (1, 2, 7, '2021-12-16', 123);


--
-- TOC entry 3112 (class 0 OID 21372)
-- Dependencies: 211
-- Data for Name: экзамен; Type: TABLE DATA; Schema: public; Owner: ses
--

INSERT INTO public."экзамен" ("idэкзамен", "idуч_план", "idстудент", "idоценка", "даты_сдачи") VALUES (1, 5, 123, 1, '{2021-06-15,2021-06-15,2021-06-15}');
INSERT INTO public."экзамен" ("idэкзамен", "idуч_план", "idстудент", "idоценка", "даты_сдачи") VALUES (2, 7, 456, NULL, NULL);


--
-- TOC entry 3131 (class 0 OID 0)
-- Dependencies: 204
-- Name: группа_idгруппа_seq; Type: SEQUENCE SET; Schema: public; Owner: ses
--

SELECT pg_catalog.setval('public."группа_idгруппа_seq"', 2, true);


--
-- TOC entry 3132 (class 0 OID 0)
-- Dependencies: 202
-- Name: дисциплина_idдисциплина_seq; Type: SEQUENCE SET; Schema: public; Owner: ses
--

SELECT pg_catalog.setval('public."дисциплина_idдисциплина_seq"', 4, true);


--
-- TOC entry 3133 (class 0 OID 0)
-- Dependencies: 200
-- Name: оценка_idоценка_seq; Type: SEQUENCE SET; Schema: public; Owner: ses
--

SELECT pg_catalog.setval('public."оценка_idоценка_seq"', 1, false);


--
-- TOC entry 3134 (class 0 OID 0)
-- Dependencies: 207
-- Name: уч_план_idуч_план_seq; Type: SEQUENCE SET; Schema: public; Owner: ses
--

SELECT pg_catalog.setval('public."уч_план_idуч_план_seq"', 8, true);


--
-- TOC entry 3135 (class 0 OID 0)
-- Dependencies: 210
-- Name: экзамен_idэкзамен_seq; Type: SEQUENCE SET; Schema: public; Owner: ses
--

SELECT pg_catalog.setval('public."экзамен_idэкзамен_seq"', 2, true);


--
-- TOC entry 2910 (class 2606 OID 21273)
-- Name: группа группа_idгруппа_check; Type: CHECK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE public."группа"
    ADD CONSTRAINT "группа_idгруппа_check" CHECK (("idгруппа" > 0)) NOT VALID;


--
-- TOC entry 2934 (class 2606 OID 20748)
-- Name: группа группа_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."группа"
    ADD CONSTRAINT "группа_pkey" PRIMARY KEY ("idгруппа");


--
-- TOC entry 2936 (class 2606 OID 21639)
-- Name: группа группа_название_описание_key; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."группа"
    ADD CONSTRAINT "группа_название_описание_key" UNIQUE ("название", "описание");


--
-- TOC entry 2906 (class 2606 OID 21274)
-- Name: дисциплина дисциплина_idдисциплина_check; Type: CHECK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE public."дисциплина"
    ADD CONSTRAINT "дисциплина_idдисциплина_check" CHECK (("idдисциплина" > 0)) NOT VALID;


--
-- TOC entry 2929 (class 2606 OID 20732)
-- Name: дисциплина дисциплина_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."дисциплина"
    ADD CONSTRAINT "дисциплина_pkey" PRIMARY KEY ("idдисциплина");


--
-- TOC entry 2931 (class 2606 OID 21637)
-- Name: дисциплина дисциплина_описание_название_key; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."дисциплина"
    ADD CONSTRAINT "дисциплина_описание_название_key" UNIQUE ("описание", "название");


--
-- TOC entry 2924 (class 2606 OID 20699)
-- Name: оценка оценка_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."оценка"
    ADD CONSTRAINT "оценка_pkey" PRIMARY KEY ("idоценка");


--
-- TOC entry 2926 (class 2606 OID 21234)
-- Name: оценка оценка_название_key; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."оценка"
    ADD CONSTRAINT "оценка_название_key" UNIQUE ("название");


--
-- TOC entry 2919 (class 2606 OID 21275)
-- Name: преподаватель преподаватель_idпреподаватель_check; Type: CHECK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE public."преподаватель"
    ADD CONSTRAINT "преподаватель_idпреподаватель_check" CHECK (("idпреподаватель" > 0)) NOT VALID;


--
-- TOC entry 2946 (class 2606 OID 21152)
-- Name: преподаватель преподаватель_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."преподаватель"
    ADD CONSTRAINT "преподаватель_pkey" PRIMARY KEY ("idпреподаватель");


--
-- TOC entry 2916 (class 2606 OID 21276)
-- Name: студент студент_idстудент_check; Type: CHECK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE public."студент"
    ADD CONSTRAINT "студент_idстудент_check" CHECK (("idстудент" > 0)) NOT VALID;


--
-- TOC entry 2943 (class 2606 OID 20889)
-- Name: студент студент_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."студент"
    ADD CONSTRAINT "студент_pkey" PRIMARY KEY ("idстудент");


--
-- TOC entry 2938 (class 2606 OID 21155)
-- Name: уч_план уч_план_idдисциплина_idгруппа_idпр_key; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план"
    ADD CONSTRAINT "уч_план_idдисциплина_idгруппа_idпр_key" UNIQUE ("idдисциплина", "idгруппа", "idпреподаватель");


--
-- TOC entry 2913 (class 2606 OID 21277)
-- Name: уч_план уч_план_idуч_план_check; Type: CHECK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE public."уч_план"
    ADD CONSTRAINT "уч_план_idуч_план_check" CHECK (("idуч_план" > 0)) NOT VALID;


--
-- TOC entry 2940 (class 2606 OID 20842)
-- Name: уч_план уч_план_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план"
    ADD CONSTRAINT "уч_план_pkey" PRIMARY KEY ("idуч_план");


--
-- TOC entry 2948 (class 2606 OID 21384)
-- Name: экзамен экзамен_idуч_план_idстудент_key; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен"
    ADD CONSTRAINT "экзамен_idуч_план_idстудент_key" UNIQUE ("idуч_план", "idстудент");


--
-- TOC entry 2950 (class 2606 OID 21382)
-- Name: экзамен экзамен_pkey; Type: CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен"
    ADD CONSTRAINT "экзамен_pkey" PRIMARY KEY ("idэкзамен");


--
-- TOC entry 2927 (class 1259 OID 21642)
-- Name: index_dis_name; Type: INDEX; Schema: public; Owner: ses
--

CREATE INDEX index_dis_name ON public."дисциплина" USING btree ("название");


--
-- TOC entry 2932 (class 1259 OID 21641)
-- Name: index_gr_name; Type: INDEX; Schema: public; Owner: ses
--

CREATE INDEX index_gr_name ON public."группа" USING btree ("название");


--
-- TOC entry 2944 (class 1259 OID 21643)
-- Name: index_prep_password; Type: INDEX; Schema: public; Owner: ses
--

CREATE INDEX index_prep_password ON public."преподаватель" USING btree ("пароль");


--
-- TOC entry 2941 (class 1259 OID 21644)
-- Name: index_st_password; Type: INDEX; Schema: public; Owner: ses
--

CREATE INDEX index_st_password ON public."студент" USING btree ("пароль");


--
-- TOC entry 2965 (class 2620 OID 21197)
-- Name: уч_план change_student_of_exam; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER change_student_of_exam AFTER UPDATE ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.change_exam_of_plan();


--
-- TOC entry 2964 (class 2620 OID 21193)
-- Name: уч_план check_date_for_add_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_add_plan BEFORE INSERT ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.check_date_of_plan_ex();


--
-- TOC entry 2963 (class 2620 OID 21192)
-- Name: уч_план check_date_for_change_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_change_plan BEFORE UPDATE ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.check_date_of_plan_ex();


--
-- TOC entry 2958 (class 2620 OID 21218)
-- Name: дисциплина check_date_for_remove_discipline; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_remove_discipline BEFORE UPDATE ON public."дисциплина" FOR EACH ROW EXECUTE FUNCTION public.check_remove_discipline();


--
-- TOC entry 2959 (class 2620 OID 21224)
-- Name: группа check_date_for_remove_group; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_remove_group BEFORE UPDATE ON public."группа" FOR EACH ROW EXECUTE FUNCTION public.check_remove_group();


--
-- TOC entry 2966 (class 2620 OID 21228)
-- Name: уч_план check_date_for_remove_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_remove_plan BEFORE DELETE ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.check_remove_plan();


--
-- TOC entry 2970 (class 2620 OID 21221)
-- Name: преподаватель check_date_for_remove_teacher; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_date_for_remove_teacher BEFORE UPDATE ON public."преподаватель" FOR EACH ROW EXECUTE FUNCTION public.check_remove_teacher();


--
-- TOC entry 2961 (class 2620 OID 21187)
-- Name: уч_план check_for_add_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_for_add_plan BEFORE INSERT ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.check_data_for_plan();


--
-- TOC entry 2962 (class 2620 OID 21188)
-- Name: уч_план check_for_mod_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER check_for_mod_plan BEFORE UPDATE ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.check_data_for_plan();


--
-- TOC entry 2960 (class 2620 OID 21184)
-- Name: уч_план create_ex_of_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER create_ex_of_plan AFTER INSERT ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.add_exam_to_plan();


--
-- TOC entry 2969 (class 2620 OID 20922)
-- Name: студент inc_group_stud; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER inc_group_stud AFTER INSERT ON public."студент" FOR EACH ROW EXECUTE FUNCTION public.add_student_to_group();


--
-- TOC entry 2967 (class 2620 OID 21266)
-- Name: уч_план remove_exam_after_plan; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER remove_exam_after_plan BEFORE DELETE ON public."уч_план" FOR EACH ROW EXECUTE FUNCTION public.remove_exam();


--
-- TOC entry 2968 (class 2620 OID 21243)
-- Name: студент upd_group_stud; Type: TRIGGER; Schema: public; Owner: ses
--

CREATE TRIGGER upd_group_stud BEFORE UPDATE ON public."студент" FOR EACH ROW EXECUTE FUNCTION public.student_update();


--
-- TOC entry 2951 (class 2606 OID 20816)
-- Name: уч_план курс_idгруппа_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план"
    ADD CONSTRAINT "курс_idгруппа_fkey" FOREIGN KEY ("idгруппа") REFERENCES public."группа"("idгруппа");


--
-- TOC entry 2952 (class 2606 OID 20821)
-- Name: уч_план курс_idдисциплина_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план"
    ADD CONSTRAINT "курс_idдисциплина_fkey" FOREIGN KEY ("idдисциплина") REFERENCES public."дисциплина"("idдисциплина");


--
-- TOC entry 2953 (class 2606 OID 21156)
-- Name: уч_план курс_idпреподаватель_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."уч_план"
    ADD CONSTRAINT "курс_idпреподаватель_fkey" FOREIGN KEY ("idпреподаватель") REFERENCES public."преподаватель"("idпреподаватель") NOT VALID;


--
-- TOC entry 2954 (class 2606 OID 20890)
-- Name: студент студент_idгруппа_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."студент"
    ADD CONSTRAINT "студент_idгруппа_fkey" FOREIGN KEY ("idгруппа") REFERENCES public."группа"("idгруппа");


--
-- TOC entry 2955 (class 2606 OID 21385)
-- Name: экзамен экзамен_idоценка_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен"
    ADD CONSTRAINT "экзамен_idоценка_fkey" FOREIGN KEY ("idоценка") REFERENCES public."оценка"("idоценка");


--
-- TOC entry 2956 (class 2606 OID 21390)
-- Name: экзамен экзамен_idстудент_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен"
    ADD CONSTRAINT "экзамен_idстудент_fkey" FOREIGN KEY ("idстудент") REFERENCES public."студент"("idстудент");


--
-- TOC entry 2957 (class 2606 OID 21395)
-- Name: экзамен экзамен_idуч_план_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ses
--

ALTER TABLE ONLY public."экзамен"
    ADD CONSTRAINT "экзамен_idуч_план_fkey" FOREIGN KEY ("idуч_план") REFERENCES public."уч_план"("idуч_план");


--
-- TOC entry 3119 (class 0 OID 0)
-- Dependencies: 205
-- Name: TABLE "группа"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT,INSERT,TRIGGER,UPDATE ON TABLE public."группа" TO ses_admin;
GRANT SELECT ON TABLE public."группа" TO ses_prep;


--
-- TOC entry 3121 (class 0 OID 0)
-- Dependencies: 203
-- Name: TABLE "дисциплина"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT,INSERT,TRIGGER,UPDATE ON TABLE public."дисциплина" TO ses_admin;
GRANT SELECT ON TABLE public."дисциплина" TO ses_prep;
GRANT SELECT ON TABLE public."дисциплина" TO ses_stud;


--
-- TOC entry 3123 (class 0 OID 0)
-- Dependencies: 201
-- Name: TABLE "оценка"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT ON TABLE public."оценка" TO ses_admin;
GRANT SELECT ON TABLE public."оценка" TO ses_prep;
GRANT SELECT ON TABLE public."оценка" TO ses_stud;
GRANT SELECT ON TABLE public."оценка" TO ses_user;


--
-- TOC entry 3125 (class 0 OID 0)
-- Dependencies: 209
-- Name: TABLE "преподаватель"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT,INSERT,TRIGGER,UPDATE ON TABLE public."преподаватель" TO ses_admin;
GRANT SELECT ON TABLE public."преподаватель" TO ses_prep;
GRANT SELECT ON TABLE public."преподаватель" TO ses_stud;
GRANT SELECT ON TABLE public."преподаватель" TO ses_user;


--
-- TOC entry 3126 (class 0 OID 0)
-- Dependencies: 208
-- Name: TABLE "студент"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT,INSERT,TRIGGER,UPDATE ON TABLE public."студент" TO ses_admin;
GRANT SELECT ON TABLE public."студент" TO ses_prep;
GRANT SELECT ON TABLE public."студент" TO ses_user;


--
-- TOC entry 3127 (class 0 OID 0)
-- Dependencies: 206
-- Name: TABLE "уч_план"; Type: ACL; Schema: public; Owner: ses
--

GRANT ALL ON TABLE public."уч_план" TO ses_admin;
GRANT SELECT ON TABLE public."уч_план" TO ses_prep;
GRANT SELECT ON TABLE public."уч_план" TO ses_stud;


--
-- TOC entry 3129 (class 0 OID 0)
-- Dependencies: 211
-- Name: TABLE "экзамен"; Type: ACL; Schema: public; Owner: ses
--

GRANT SELECT ON TABLE public."экзамен" TO ses_stud;
GRANT TRIGGER,UPDATE ON TABLE public."экзамен" TO ses_prep;
GRANT ALL ON TABLE public."экзамен" TO ses_admin;


-- Completed on 2021-06-25 10:30:06 +04

--
-- PostgreSQL database dump complete
--

