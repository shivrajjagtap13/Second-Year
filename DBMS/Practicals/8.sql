/*
8. Unnamed PL/SQLcode block: 
	Use of Control structure and Exception handling is mandatory.
*/

show databases;
use studentdb;

delimiter $$
create procedure grades(in a int)
begin 
    declare continue handler for sqlexception
    select "Error occurred" as message;
    if a>=90 then 
    select "Excellent" as grade;
    elseif a>=75 and a<90 then 
    select "Good" as grade;
    elseif a>=40 and a<75 then 
    select "Pass" as grade;
    else
    select "Fail" as grade;
    end if;
end $$
delimiter ;

call grades(45);   
    