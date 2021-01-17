select r.reservation_id, o.order_id from reservations r
inner join orders o on
r.customer_id = o.customer_id
and r.date_start_time=o.order_date
order by reservation_id;
--- połączy odpowiednie rezerwacje z zamówieniami