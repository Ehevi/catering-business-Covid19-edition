--- uzupełnienie tabeli CUSTOMERS_DISCOUNTS dla klientów spełniających kryteria programu rabatowego o id=2
--- tak samo jak dla programu pierwszego, tylko program startuje po 20 zamówieniach (10 poprzednich + kolejne 10)
declare @i int=1;
while(@i<3000)
begin
with cte as (select top 20 o.order_id, o.order_date, o.customer_id, sum(od.item_price*od.item_quantity) as 'suma zamówienia'
    from orders o inner join order_details od
    on o.order_id=od.order_id
    where o.customer_id=@i and o.status=4
    group by o.order_id, o.order_date, o.customer_id
    having sum(od.item_price*od.item_quantity)>30)
insert into customers_discounts(customer_id, program_id, date_start_time)
select customer_id, 2, max(order_date) from cte
where customer_id in (select customer_id from individual)
group by customer_id
set @i = @i + 1
end;
