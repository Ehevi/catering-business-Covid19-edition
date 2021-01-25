--- dla programu rabatowego 1
declare @order_id int = 1;
while (@order_id<667802)
begin
	if(@order_id) in (
		select order_id
		from orders o inner join customers_discounts cd
			on o.customer_id=cd.customer_id
				and o.order_date>=date_start_time
		where program_id=1)
	declare @item_id int=0;
	while(@item_id<646)
	begin
		set @item_id=@item_id +1;
        if(@item_id in (select item_id from order_details od1 where order_id=@order_id))
		update order_details
		set item_discount=(
			select item_price*3/cast(100 as float)
			from order_details
			where order_id=@order_id
				and item_id=@item_id)
		where order_id=@order_id
			and item_id=@item_id
	end
    set @order_id=@order_id+1;
end

--- dla programu rabatowego 2
declare @order_id int = 1;
while (@order_id<667801)
begin
	if(@order_id) in (
		select order_id
		from orders o inner join customers_discounts cd
			on o.customer_id=cd.customer_id
				and o.order_date>=date_start_time
		where program_id=2)
	declare @item_id int=0;
	while(@item_id<646)
	begin
		set @item_id=@item_id +1;
		if(@item_id in (select item_id from order_details od1 where order_id=@order_id))
		update order_details
		set item_discount=(select item_discount from order_details
			where order_id=@order_id
				and item_id=@item_id)*2
		where order_id=@order_id
			and item_id=@item_id
	end
	set @order_id=@order_id+1;
end