use temp;
select *from account;
select *from bonus;
select *from customer;
select *from title;
select *from worker;


select worker_title,count(worker_title) from title group by worker_title having count(worker_title)>1;

-- SQL query to show only odd rows;
select *from worker where MOD (worker_id,2)!=0;

-- sql query to show only even rows;
select *from worker where MOD(worker_id,2)=0;

-- Clone a table to create another table
create table worker_clone like worker;
desc worker_clone;
insert into worker_clone select *from worker;
select *from worker_clone;

-- Intersection of two tables;
-- Here Intersect is not available
select worker.*,worker_clone.* from worker natural join worker_clone;
select worker.* from worker inner join worker_clone using(worker_id); 

-- write an sql query to show data of one table that other table doesnt have
-- here MINUS is not available
select *from worker left join worker_clone using (worker_id) where worker_clone.worker_id = NULL;

-- write sql query to show current date and time
select sysdate();
select curdate();
select now();

-- write a sql query to show only top 5 data by salary in desc order
select *from worker order by(salary) desc limit 5;

-- write sql query for displaying name of worker with second highest salary ;
select firstname from worker where salary = (select max(salary) as m from worker where salary!=(select max(salary) as m2 from worker));

-- select nth highest salary(5th)
-- it gives the first row except first r rows
select salary from worker order by(salary) desc limit 4,1;

-- write query to select 5 th highest salary without using limit
select salary from worker w2 where 5 = (select count(distinct salary) from worker w1 where w1.salary>=w2.salary) order by salary desc ;


-- sql query to show employee with same salary
insert into worker values(7,'rutik','khot',80000,'2023-01-01','IT');
select w.firstname from worker w where w.salary = (select salary from worker where salary = w.salary and firstname!=w.firstname);
-- or
select w1.*,w2.* from worker w1,worker w2 where w1.salary = w2.salary and w1.firstname !=w2.firstname;

-- show each row twice in table
select *from worker
union all 
select *from worker;

-- workers who didnt get bonus
select worker_id from worker where worker_id not in (select worker_ref_id from bonus);

-- sql query to select 50%records from a table
-- in this problem , we already know that the worker ids are auto incremented, so will use that in our subquery
select *from worker where worker_id <= (select count(worker_id)/2 from worker);


-- sql query to determine the department which has less than 2 employee in it
select department from worker group by department  having count(worker_id)<2 ;

-- sql query to show no of employee and department ;
select count(worker_id),department from worker group by department;

-- sql query to show last record from table;
select *from worker where worker_id = (select count(worker_id) from worker);
-- OR
select *from worker where worker_id = (select max(worker_id) from worker);


-- sql query to show the first record
select *from worker where worker_id = (select min(worker_id) from worker);

-- sql query to show the last 4 rows
(select *from worker order by worker_id desc limit 4) order by worker_id;

-- sql query to print name of employee having highest salary in each department
select firstname,salary,department from worker where salary in (select max(salary) from worker group by department);
-- OR
select max(salary),department from worker group by department;

-- sql query to print three max salaries from table without using limit
select distinct salary from worker w1
where 3>= (select count(distinct salary) from  worker w2 where w1.salary<=w2.salary) order by w1.salary desc;
-- OR
select firstname, salary from worker order by salary desc limit 3;

-- sql query to print three min salaries from table without using limit
select distinct salary from worker w1
 where 3>=(select count(distinct salary) from worker w2 where w1.salary>=w2.salary) order by salary;
 
 -- sql query to select nth max salary
 select distinct salary from worker w1
 where 4=(select count(distinct salary) from worker w2 where w2.salary>=w1.salary) order by salary desc;
 
 -- sql query to fetch department and total salary paid for each departmen
 select department,sum(salary) from worker group by department;