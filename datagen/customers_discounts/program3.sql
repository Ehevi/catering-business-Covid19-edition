--- wyświetl aktualną sumę za wszystkie zamówienia złożone w przeszłości przez klientów
--- wliczamy tylko zrealizowane zamówienia (status: 4)
select customer_id, sum(od.item_price*od.item_quantity)
from orders o inner join order_details od
on o.order_id=od.order_id
where o.order_date<GETDATE() and o.status=4
group by customer_id
order by customer_id

--- suma za wszystkie poprzednie zamówienia (złożone do czasu analizowanego teraz zamówienia)
declare @i int=1
while(@i<667801) --- ostatnie zamówienie w tabeli
begin
	select customer_id, sum(od.item_price*od.item_quantity)
	from orders o inner join order_details od
	on o.order_id=od.order_id
	where o.order_id<@i and o.status=4
	group by customer_id
	order by customer_id
	set @i = @i + 1
end;