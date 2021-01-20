--- numer zamówienia + jego suma
select o.order_id, sum(od.item_price*od.item_quantity)
from order_details od inner join orders o
on od.order_id=o.order_id
group by o.order_id

--- numer klienta + numer zamówienia + suma zamówienia
select o.customer_id, o.order_id, sum(od.item_price*od.item_quantity)
from order_details od inner join orders o
on od.order_id=o.order_id
group by o.order_id, o.customer_id
order by o.customer_id, o.order_id

--- ile zamówień złożył klient + suma tych zamówień dla zamówień o id <5000 i klienta o id=1
with cte as (select o.customer_id, o.order_id, sum(od.item_price*od.item_quantity) s
from order_details od inner join orders o
on od.order_id=o.order_id
group by o.order_id, o.customer_id)
select count(order_id), sum(s)
from cte
where cte.customer_id=1 and cte.order_id<5000
group by cte.customer_id

--- ile zamówień złożył klient o id=1 i ile do wtedy zapłacił za swoje poprzednie zamówienia
--- tablica pomocnicza do przechowywania wyników
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[newTable](
	[customer_id] [int] NOT NULL,
	[orders_no] [int] NOT NULL,
	[sum] [int] NOT NULL,
 CONSTRAINT [PK_newTable] PRIMARY KEY CLUSTERED 
(
	[customer_id], [orders_no], [sum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

--- wpisywanie danych do tabeli newTable
declare @i int = 1
while(@i<667801)
begin
with cte as (select o.customer_id, o.order_id, sum(od.item_price*od.item_quantity) s
from order_details od inner join orders o
on od.order_id=o.order_id
group by o.order_id, o.customer_id)
insert into newTable(customer_id, orders_no, sum)
select 1, count(order_id), sum(s)
from cte
where cte.customer_id=1 and cte.order_id<@i
group by cte.customer_id
set @i = @i +1
end

--- uzupełnienie tabeli newTable dla wszystkich klientów: // najpierw wyczyszczenie z tabeli poprzednich danych
--- (numer klienta, liczba złożonych zamówień, suma za te zamówienia)
declare @i int = 1
declare @customer_id int =1
while(@customer_id<3000)
begin
	set @i = 1
	while(@i<667801)
	begin
		with cte as (select o.customer_id, o.order_id, sum(od.item_price*od.item_quantity) s
		from order_details od inner join orders o
		on od.order_id=o.order_id
		where o.customer_id=@customer_id and o.status=4 and o.customer_id in (select customer_id from individual)
		group by o.order_id, o.customer_id)
		insert into newTable(customer_id, orders_no, sum)
		select @customer_id, count(order_id), sum(s)
		from cte
		where cte.customer_id=@customer_id and cte.order_id<@i
		group by cte.customer_id
		set @i = @i +1
		if((select max(sum) from newTable where customer_id=@customer_id)>5000) break
	end
set @customer_id=@customer_id+1
end

--- K2 = 1000, K3=5000 [dlatego uzupełniamy tabelę newTable dopóki suma za dotychczasowe zamówienia jest mniejsza od 5000]

--- optymalizacja
declare @i int = 1
declare @customer_id int =1
while(@customer_id<3000)
begin
	if(@customer_id in (select customer_id from individual))
	begin
		set @i = 1
		while(@i<667801)
		begin
			with cte as (select o.customer_id, o.order_id, sum(od.item_price*od.item_quantity) s
			from order_details od inner join orders o
			on od.order_id=o.order_id
			where o.customer_id=@customer_id and o.status=4 and o.customer_id in (select customer_id from individual)
			group by o.order_id, o.customer_id)
			insert into newTable(customer_id, orders_no, sum)
			select @customer_id, count(order_id), sum(s)
			from cte
			where cte.customer_id=@customer_id and cte.order_id<@i
			group by cte.customer_id
			set @i = @i +1
			if((select max(sum) from newTable where customer_id=@customer_id)>5000) break
		end
	end
set @customer_id=@customer_id+1
end