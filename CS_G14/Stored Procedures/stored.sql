--1. Count number of soldiers belonging to a particular squad
SET SEARCH_PATH TO armydb;
CREATE OR REPLACE FUNCTION countSold(sqNo varchar) RETURNS INTEGER AS
$BODY$
DECLARE
edno integer;
id soldier%ROWTYPE;
BEGIN
  edno = 0;
  FOR id IN SELECT * from soldier AS s where s.squadno = sqNo LOOP
      if id IS NOT NULL THEN
        edno = edno + 1;
      END IF;
  END LOOP;
  RETURN edno;
END
$BODY$ LANGUAGE plpgsql;

--2. Count number of soldiers which have greater than or equal to 2 medals.
SET SEARCH_PATH to armydb;
CREATE or REPLACE FUNCTION countmedals(count integer) RETURNS INTEGER AS
$BODY$
DECLARE
edno INTEGER;
t INTEGER;
id soldier%ROWTYPE;
BEGIN
  edno = 0;
  FOR id IN SELECT * FROM soldier AS s JOIN reward as r ON (s.id = r.id) LOOP
    t = count(id);
    if t >= count THEN
      edno = edno + 1;
    END IF;
  END LOOP;
  RETURN edno;
END;
$BODY$ LANGUAGE plpgsql;

--3. count number of soldiers Which belong to same Height
SET SEARCH_PATH to armydb;
CREATE or REPLACE FUNCTION  countID_height(ht integer) RETURNS INTEGER AS
$BODY$
DECLARE
edno INTEGER;
id soldier%ROWTYPE;
BEGIN
  edno = 0;
  FOR id IN SELECT * from soldier AS s where s.Height = ht LOOP
      if id IS NOT NULL THEN
        edno = edno + 1;
      END IF;
  END LOOP;
  RETURN edno;
END
$BODY$ LANGUAGE plpgsql;

--4.count number of soldiers Which belong to same Weight
SET SEARCH_PATH to armydb;
CREATE or REPLACE FUNCTION  countID_weight(wt integer) RETURNS INTEGER AS
$BODY$
DECLARE
edno INTEGER;
id soldier%ROWTYPE;
BEGIN
  edno = 0;
  FOR id IN SELECT * from soldier AS s where s.Weight = wt LOOP
      if id IS NOT NULL THEN
        edno = edno + 1;
      END IF;
  END LOOP;
  RETURN edno;
END
$BODY$ LANGUAGE plpgsql;

--5.count number of soldiers Which belong to same Location
SET SEARCH_PATH to armydb;
CREATE or REPLACE FUNCTION  countID_same_place(pin varchar) RETURNS INTEGER AS
$BODY$
DECLARE
edno INTEGER;
id soldier%ROWTYPE;
BEGIN
  edno = 0;
  FOR id IN SELECT * from soldier AS s where s.BirthPlacePinCode = pin LOOP
      if id IS NOT NULL THEN
        edno = edno + 1;
      END IF;
  END LOOP;
  RETURN edno;
END
$BODY$ LANGUAGE plpgsql;


--6.count the numbers of weapons which belong to same orgname
SET SEARCH_PATH to armydb;
CREATE or REPLACE FUNCTION  countSerialno_sameOrg(name varchar, location varchar) RETURNS INTEGER AS
$BODY$
DECLARE
edno INTEGER;
serialno manufacturingdetails%ROWTYPE;
BEGIN
  edno = 0;
  FOR serialno IN SELECT * from manufacturingdetails AS m where m.orgName = name and m.ManufacturingLocation = location LOOP
      if serialno IS NOT NULL THEN
        edno = edno + 1;
      END IF;
  END LOOP;
  RETURN edno;
END
$BODY$ LANGUAGE plpgsql;

--7. Count number of weapons which are less than 10 years old from the current date
SET SEARCH_PATH to armydb;
CREATE OR REPLACE FUNCTION countWeapons(no integer) RETURNS INTEGER AS
  $BODY$
  DECLARE
  edno INTEGER;
  serial weapons%ROWTYPE;
  BEGIN
    edno = 0;
    FOR serial IN SELECT serial_no FROM weapons AS w
      JOIN (SELECT * FROM soldier AS s JOIN inventory AS i ON (s.id = i.id)) AS r1 ON (w.serialno = r1.serial_no)
      WHERE EXTRACT(YEAR FROM current_date) - EXTRACT(YEAR FROM r1.doj) >= no LOOP
        edno = edno+1;
    END LOOP;
    RETURN  edno;
  END;
  $BODY$ LANGUAGE plpgsql;


--8. Show wepaons belonging to the any organisation
SET SEARCH_PATH to armydb;
CREATE TYPE weaponInfo AS (
       name varchar(70),
       serialno integer,
       class_ varchar(70)
);
CREATE OR REPLACE FUNCTION countWeaponsInfo(nameC varchar) RETURNS TABLE (
  name varchar(70),
  serialno integer,
  class_ varchar(70)
) AS
 $BODY$
 BEGIN
	RETURN QUERY
	SELECT wep.name_, wep.serialno, cat.class_
	from manufacturingdetails
	inner join weapons as wep on wep.serialno = manufacturingdetails.serial_no
	inner join cateogry as cat on cat.name_ = wep.name_
	where manufacturingdetails.orgname = nameC;
 END;
 $BODY$ LANGUAGE plpgsql;

--9. Update the Salary of a particular type
set search_path to armydb;
CREATE OR REPLACE FUNCTION changeType(type varchar, no integer) RETURNS VOID AS
$BODY$
BEGIN
	UPDATE work set salary = salary + no
	where type_ = type;
END;
$BODY$ LANGUAGE plpgsql;




