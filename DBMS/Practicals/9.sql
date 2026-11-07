/*
9. Write a PL/SQL block of code using parameterized Cursor 
that will merge the data available in the newly created table N_Roll_Call 
with the data available in the table O_Roll_Call. 

If the data in the first table already exists in the second table 
then that data should be skipped.

*/

show databases;
use studentDB;

delimiter $$
create procedure Merge_roll_call()
begin
	declare done int default 0;
    declare v_rollno int;
    declare v_name varchar(30);
     declare cur1 cursor for 
		select roll_no, name from New_rollcall;
    declare continue handler for not found set done =1;
    
    open cur1;
    
    read_loop : loop
		fetch cur1 into v_rollno, v_name;
        
        if done=1 then
			leave read_loop;
		end if ;
	
    if not exists (select 1 from old_rollcall where roll_no = v_rollno) then 
		insert into old_rollcall(roll_no, name) values(v_rollno, v_name);
	end if;
end loop;
    
    close cur1;
end $$
delimiter ;
        
    