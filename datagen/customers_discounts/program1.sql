--- wyświetl sumy wszystkich zamówień klienta o id=1
select o.order_id, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
from orders o inner join order_details od
on o.order_id=od.order_id
where o.customer_id=1
group by o.order_id

--- sumy wszystkich zamówień klienta o id=1 za minimum 30zł
select o.order_id, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
from orders o inner join order_details od
on o.order_id=od.order_id
where o.customer_id=1
group by o.order_id
having sum(od.item_price*od.item_quantity)>=30;

--- sumy wszystkich zamówień klienta o id=1 za minimum 30zł razem z datą zamówienia
select o.order_id, o.order_date, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
from orders o inner join order_details od
on o.order_id=od.order_id
where o.customer_id=1
group by o.order_id, o.order_date
having sum(od.item_price*od.item_quantity)>=30;

--- sumy wszystkich zamówień klienta o id=1 za minimum 30zł razem z datą zamówienia, ale tylko dla zamówień zrealizowanych
select o.order_id, o.order_date, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
from orders o inner join order_details od
on o.order_id=od.order_id
where o.customer_id=1 and o.status=4
group by o.order_id, o.order_date
having sum(od.item_price*od.item_quantity)>=30;

--- ograniczone do 10 pierwszych zamówień
select top 10 o.order_id, o.order_date, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
from orders o inner join order_details od
on o.order_id=od.order_id
where o.customer_id=1 and o.status=4
group by o.order_id, o.order_date
having sum(od.item_price*od.item_quantity)>30;

--- data, od której klient o id=1 spełnia wymogi programu rabatowego o id=1
with cte as (select top 10 o.order_id, o.order_date, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
    from orders o inner join order_details od
    on o.order_id=od.order_id
    where o.customer_id=1 and o.status=4
    group by o.order_id, o.order_date
    having sum(od.item_price*od.item_quantity)>30)
select max(order_date) from cte;

--- uzupełnienie tabeli CUSTOMERS_DISCOUNTS dla klientów spełniających kryteria programu rabatowego o id=1
declare @i int=1;
while(@i<3000)
begin
with cte as (select top 10 o.order_id, o.order_date, o.customer_id, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
    from orders o inner join order_details od
    on o.order_id=od.order_id
    where o.customer_id=@i and o.status=4
    group by o.order_id, o.order_date, o.customer_id
    having sum(od.item_price*od.item_quantity)>30)
insert into customers_discounts(customer_id, program_id, date_start_time)
select customer_id, 1, max(order_date) from cte
where customer_id in (select customer_id from individual)
group by customer_id
set @i = @i + 1
end;
