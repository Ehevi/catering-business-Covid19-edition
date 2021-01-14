--- przyporządkowanie order_id do opdowiedniego menu_id
select orders.order_id, menu.menu_id
from orders inner join menu
	on convert(date, orders.order_date) >= menu.since_date and convert(date, orders.order_date) <= menu.due_date
where menu_id=4
order by order_id

--- menu należące do jednego zbioru {1, 4, 7, ...}, {2, 5, 8, ...}, {3, 6, 9, ...} mają takie same itemy
--- wszystkie itemy należące do danego menu
select item_id
from menu_details
where menu_id=1;