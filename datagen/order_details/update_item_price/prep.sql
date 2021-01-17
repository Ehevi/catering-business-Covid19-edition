select od.order_id, od.item_id, md.item_id, od.item_price, md.item_price
from order_details od
inner join orders o on od.order_id=o.order_id
inner join menu m on cast(o.order_date as date)>= m.since_date and cast(o.order_date as date)<= m.due_date
inner join menu_details md on m.menu_id=md.menu_id
where md.item_id=od.item_id