# Opisy tabel
[Address](tableDescriptions.md), [Cities](tableDescriptions.md)
### ADDRESS
Tabela przechowująca dane o adresach osobowych i firmowych
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[address](
	[address_id] [int] IDENTITY(1,1) NOT NULL,
	[street] [nvarchar](50) NOT NULL,
	[city_id] [int] NOT NULL,
 CONSTRAINT [PK_address] PRIMARY KEY CLUSTERED 
(
	[address_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[address]
WITH CHECK ADD
	CONSTRAINT [FK_address_cities] FOREIGN KEY([city_id])
	REFERENCES [dbo].[cities] ([city_id])
GO

ALTER TABLE [dbo].[address]
CHECK CONSTRAINT [FK_address_cities]
GO
```

### CATEGORIES
Tabela przechowująca dane o kategoriach potraw znajdujących się w menu (np. _owoce morza_)
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[categories](
	[category_id] [int] IDENTITY(1,1) NOT NULL,
	[category_name] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_categories] PRIMARY KEY CLUSTERED 
(
	[category_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CITIES
Tabela przechowująca dane o miastach znajdujących się w bazie danych
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[cities](
	[city_id] [int] IDENTITY(1,1) NOT NULL,
	[city_name] [nvarchar](50) NOT NULL,
	[country_id] [int] NOT NULL,
 CONSTRAINT [PK_cities] PRIMARY KEY CLUSTERED 
(
	[city_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[cities]
WITH CHECK ADD
	CONSTRAINT [FK_cities_countries] FOREIGN KEY([country_id])
	REFERENCES [dbo].[countries] ([country_id])
GO

ALTER TABLE [dbo].[cities]
CHECK CONSTRAINT [FK_cities_countries]
GO
```

### COMPANIES
Tabela przechowująca dane o klientach firmowych.
email: unikalny i zawiera '@'
NIP: 10 cyfr(znaki numeryczne), unikalny
phone: unikalny, wyłącznie znaki numeryczne
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[companies](
	[company_id] [int] IDENTITY(1,1) NOT NULL,
	[customer_id] [int] NOT NULL,
	[company_name] [nvarchar](50) NOT NULL,
	[address_id] [int] NOT NULL,
	[phone] [nvarchar](50) NOT NULL,
	[email] [nvarchar](50) NOT NULL,
	[NIP] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_companies] PRIMARY KEY CLUSTERED 
(
	[company_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_Company_Address] UNIQUE NONCLUSTERED 
(
	[address_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_Customer_ID] UNIQUE NONCLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[companies]
WITH CHECK ADD
	CONSTRAINT [FK_companies_address] FOREIGN KEY([address_id])
	REFERENCES [dbo].[address] ([address_id])
GO

ALTER TABLE [dbo].[companies]
CHECK CONSTRAINT [FK_companies_address]
GO

ALTER TABLE [dbo].[companies]
WITH CHECK ADD
	CONSTRAINT [FK_companies_customers] FOREIGN KEY([customer_id])
	REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[companies]
CHECK CONSTRAINT [FK_companies_customers]
GO
```

### COMPANIES_EMPLOYEES
Tabela zawierająca informacje o pracownikach klientów firmowych.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[companies_employees](
	[person_id] [int] NOT NULL,
	[company_id] [int] NOT NULL,
 CONSTRAINT [PK_companies_employees] PRIMARY KEY CLUSTERED 
(
	[person_id] ASC,
	[company_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[companies_employees]
WITH CHECK ADD
	CONSTRAINT [FK_companies_employees_companies] FOREIGN KEY([company_id])
	REFERENCES [dbo].[companies] ([company_id])
GO

ALTER TABLE [dbo].[companies_employees]
CHECK CONSTRAINT [FK_companies_employees_companies]
GO

ALTER TABLE [dbo].[companies_employees]
WITH CHECK ADD
	CONSTRAINT [FK_companies_employees_person] FOREIGN KEY([person_id])
	REFERENCES [dbo].[person] ([person_id])
GO

ALTER TABLE [dbo].[companies_employees]
CHECK CONSTRAINT [FK_companies_employees_person]
GO
```

### COUNRIES
Słownik państw występujących w adresach osobowych i firmowych.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[countries](
	[country_id] [int] IDENTITY(1,1) NOT NULL,
	[country_name] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_countries] PRIMARY KEY CLUSTERED 
(
	[country_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CUSTOMERS
Tabela przechowująca ID klientów
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[customers](
	[customer_id] [int] IDENTITY(1,1) NOT NULL,
 CONSTRAINT [PK_customers] PRIMARY KEY CLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### CUSTOMERS_DICSOUNTS
Tabela przechowująca dane o programach rabatowych poszczególnych klientów
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[customers_discounts](
	[customer_id] [int] NOT NULL,
	[program_id] [int] NOT NULL,
	[date_start_time] [datetime2](7) NOT NULL,
 CONSTRAINT [PK_customers_discounts] PRIMARY KEY CLUSTERED 
(
	[customer_id] ASC,
	[program_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[customers_discounts]
WITH CHECK ADD
	CONSTRAINT [FK_customers_discounts_customers] FOREIGN KEY([customer_id])
	REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[customers_discounts]
CHECK CONSTRAINT [FK_customers_discounts_customers]
GO

ALTER TABLE [dbo].[customers_discounts]
WITH CHECK ADD
	CONSTRAINT [FK_customers_discounts_programs] FOREIGN KEY([program_id])
	REFERENCES [dbo].[programs] ([program_id])
GO

ALTER TABLE [dbo].[customers_discounts]
CHECK CONSTRAINT [FK_customers_discounts_programs]
GO
```

### DISCOUNT_DATA
Tabela przechowująca dane dotyczące zmiennych występujących jako wartości liczbowe w poszczególnych programach rabatowych.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[discount_data](
	[discount_data_id] [int] IDENTITY(1,1) NOT NULL,
	[type] [nvarchar](50) NOT NULL,
	[value] [float] NOT NULL,
 CONSTRAINT [PK_discount_data] PRIMARY KEY CLUSTERED 
(
	[discount_data_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### DISCOUNT_DATA_IN_PROGRAMS
Tabela przechowująca informacje o tym, jakie zmienne są przyporządkowane do poszczególnych programów rabatowych.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[discount_data_in_programs](
	[discount_data_id] [int] NOT NULL,
	[program_id] [int] NOT NULL,
 CONSTRAINT [PK_discount_data_in_programs] PRIMARY KEY CLUSTERED 
(
	[discount_data_id] ASC,
	[program_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[discount_data_in_programs]
WITH CHECK ADD
	CONSTRAINT [FK_discount_data_in_programs_discount_data] FOREIGN KEY([discount_data_id])
	REFERENCES [dbo].[discount_data] ([discount_data_id])
GO

ALTER TABLE [dbo].[discount_data_in_programs]
CHECK CONSTRAINT [FK_discount_data_in_programs_discount_data]
GO

ALTER TABLE [dbo].[discount_data_in_programs]
WITH CHECK ADD
	CONSTRAINT [FK_discount_data_in_programs_programs] FOREIGN KEY([program_id])
	REFERENCES [dbo].[programs] ([program_id])
GO

ALTER TABLE [dbo].[discount_data_in_programs]
CHECK CONSTRAINT [FK_discount_data_in_programs_programs]
GO
```

### EMPLOYEES
Tabela wskazująca na dane osób pracujących w usługach gastronomicznych.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[employees](
	[employee_id] [int] NOT NULL,
 CONSTRAINT [PK_employees] PRIMARY KEY CLUSTERED 
(
	[employee_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### INDIVIDUAL
Tabela przechowująca dane o klientach indywidualnych
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[individual](
	[person_id] [int] NOT NULL,
	[customer_id] [int] NOT NULL,
 CONSTRAINT [PK_individual] PRIMARY KEY CLUSTERED 
(
	[person_id] ASC,
	[customer_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_I_Customer_ID] UNIQUE NONCLUSTERED 
(
	[customer_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_I_person_ID] UNIQUE NONCLUSTERED 
(
	[person_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[individual]
WITH CHECK ADD
	CONSTRAINT [FK_individual_customers] FOREIGN KEY([customer_id])
	REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[individual]
CHECK CONSTRAINT [FK_individual_customers]
GO

ALTER TABLE [dbo].[individual]
WITH CHECK ADD
	CONSTRAINT [FK_individual_person] FOREIGN KEY([person_id])
	REFERENCES [dbo].[person] ([person_id])
GO

ALTER TABLE [dbo].[individual]
CHECK CONSTRAINT [FK_individual_person]
GO
```

### MENU
Tabela przechowująca dane o menu
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[menu](
	[menu_id] [int] IDENTITY(1,1) NOT NULL,
	[since_date] [datetime2](7) NOT NULL,
	[due_date] [datetime2](7) NOT NULL,
 CONSTRAINT [PK_menu] PRIMARY KEY CLUSTERED 
(
	[menu_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### MENU_DETAILS
Tabela przechowująca informacje szczegółowe dotyczące poszczególnych menu.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[menu_details](
	[menu_id] [int] NOT NULL,
	[item_id] [int] NOT NULL,
	[is_available] [int] NOT NULL,
	[item_price] [money] NOT NULL,
 CONSTRAINT [PK_menu_details] PRIMARY KEY CLUSTERED 
(
	[menu_id] ASC,
	[item_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[menu_details]
WITH CHECK ADD
	CONSTRAINT [FK_menu_details_menu_items] FOREIGN KEY([item_id])
	REFERENCES [dbo].[menu_items] ([item_id])
GO

ALTER TABLE [dbo].[menu_details]
CHECK CONSTRAINT [FK_menu_details_menu_items]
GO

ALTER TABLE [dbo].[menu_details]
WITH CHECK ADD
	CONSTRAINT [FK_menu_details_menu1] FOREIGN KEY([menu_id])
	REFERENCES [dbo].[menu] ([menu_id])
GO

ALTER TABLE [dbo].[menu_details]
CHECK CONSTRAINT [FK_menu_details_menu1]
GO
```

### MENU_ITEMS
Tabela przechowująca dane dotyczące pojedynczych dań mogących występować w menu
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[menu_items](
	[item_id] [int] IDENTITY(1,1) NOT NULL,
	[item_name] [nvarchar](50) NOT NULL,
	[category_id] [int] NOT NULL,
 CONSTRAINT [PK_menu_items] PRIMARY KEY CLUSTERED 
(
	[item_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[menu_items]
WITH CHECK ADD
	CONSTRAINT [FK_menu_items_categories] FOREIGN KEY([category_id])
	REFERENCES [dbo].[categories] ([category_id])
GO

ALTER TABLE [dbo].[menu_items]
CHECK CONSTRAINT [FK_menu_items_categories]
GO
```

### ORDER_DETAILS
Tabela przechowująca szczegółowe informacje dotyczące zamówienia
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[order_details](
	[order_id] [int] NOT NULL,
	[item_id] [int] NOT NULL,
	[item_price] [money] NOT NULL,
	[item_quantity] [int] NOT NULL,
	[item_discount] [money] NOT NULL,
 CONSTRAINT [PK_order_details] PRIMARY KEY CLUSTERED 
(
	[order_id] ASC,
	[item_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[order_details]
WITH CHECK ADD
	CONSTRAINT [FK_order_details_menu_items] FOREIGN KEY([item_id])
	REFERENCES [dbo].[menu_items] ([item_id])
GO

ALTER TABLE [dbo].[order_details]
CHECK CONSTRAINT [FK_order_details_menu_items]
GO

ALTER TABLE [dbo].[order_details]
WITH CHECK ADD
	CONSTRAINT [FK_order_details_orders] FOREIGN KEY([order_id])
	REFERENCES [dbo].[orders] ([order_id])
GO

ALTER TABLE [dbo].[order_details]
CHECK CONSTRAINT [FK_order_details_orders]
GO
```

### ORDERS
Tabela przechowująca dane o składanych zamówieniach
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[orders](
	[order_id] [int] IDENTITY(1,1) NOT NULL,
	[customer_id] [int] NOT NULL,
	[employee_id] [int] NOT NULL,
	[order_date] [datetime2](7) NOT NULL,
	[collection_date] [datetime2](7) NOT NULL,
	[status] [int] NOT NULL,
 CONSTRAINT [PK_orders] PRIMARY KEY CLUSTERED 
(
	[order_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[orders]
WITH CHECK ADD
	CONSTRAINT [FK_orders_customers] FOREIGN KEY([customer_id])
	REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[orders]
CHECK CONSTRAINT [FK_orders_customers]
GO

ALTER TABLE [dbo].[orders]
WITH CHECK ADD
	CONSTRAINT [FK_orders_employees] FOREIGN KEY([employee_id])
	REFERENCES [dbo].[employees] ([employee_id])
GO

ALTER TABLE [dbo].[orders]
CHECK CONSTRAINT [FK_orders_employees]
GO

ALTER TABLE [dbo].[orders]
WITH CHECK ADD
	CONSTRAINT [FK_orders_status_dictionary] FOREIGN KEY([status])
	REFERENCES [dbo].[status_dictionary] ([status_id])
GO

ALTER TABLE [dbo].[orders]
CHECK CONSTRAINT [FK_orders_status_dictionary]
GO
```

### PERSON
Tabela przechowująca dane osobowe klientów indywidualnych, pracowników klientów firmowych oraz pracowników gastronomii
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[person](
	[person_id] [int] IDENTITY(1,1) NOT NULL,
	[first_name] [nvarchar](50) NOT NULL,
	[last_name] [nvarchar](50) NOT NULL,
	[email] [nvarchar](50) NOT NULL,
	[phone] [nvarchar](50) NOT NULL,
	[address_id] [int] NOT NULL,
 CONSTRAINT [PK_person] PRIMARY KEY CLUSTERED 
(
	[person_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [Unique_Personal_Address] UNIQUE NONCLUSTERED 
(
	[address_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[person]
WITH CHECK ADD
	CONSTRAINT [FK_person_address] FOREIGN KEY([address_id])
	REFERENCES [dbo].[address] ([address_id])
GO

ALTER TABLE [dbo].[person]
CHECK CONSTRAINT [FK_person_address]
GO

ALTER TABLE [dbo].[person]
WITH CHECK ADD
	CONSTRAINT [FK_person_employees] FOREIGN KEY([person_id])
	REFERENCES [dbo].[employees] ([employee_id])
GO

ALTER TABLE [dbo].[person]
CHECK CONSTRAINT [FK_person_employees]
GO
```

### PROGRAMS
Tabela przechowująca dane o programach rabatowych
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[programs](
	[program_id] [int] IDENTITY(1,1) NOT NULL,
	[description] [nvarchar](max) NOT NULL,
 CONSTRAINT [PK_programs] PRIMARY KEY CLUSTERED 
(
	[program_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
```

### RESERVABLE_TABLES
Tabela przechowująca dane dotyczące stolików, które można rezerwować
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[reservable_tables](
	[res_table_id] [int] IDENTITY(1,1) NOT NULL,
	[table_id] [int] NOT NULL,
	[seats_no] [int] NOT NULL,
	[since_date] [datetime2](7) NOT NULL,
	[due_date] [datetime2](7) NOT NULL,
 CONSTRAINT [PK_reservable_tables] PRIMARY KEY CLUSTERED 
(
	[res_table_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservable_tables] 
WITH CHECK ADD
	CONSTRAINT [FK_reservable_tables_tables] FOREIGN KEY([table_id])
	REFERENCES [dbo].[tables] ([table_id])
GO

ALTER TABLE [dbo].[reservable_tables]
CHECK CONSTRAINT [FK_reservable_tables_tables]
GO

ALTER TABLE [dbo].[reservable_tables]
WITH CHECK ADD
	CONSTRAINT [CK_reservable_tables] CHECK  (([seats_no]>=(0)))
GO

ALTER TABLE [dbo].[reservable_tables]
CHECK CONSTRAINT [CK_reservable_tables]
GO

ALTER TABLE [dbo].[reservable_tables]  WITH CHECK ADD  CONSTRAINT [CK_reservable_tables_1] CHECK  (([since_date]<[due_date]))
GO

ALTER TABLE [dbo].[reservable_tables] CHECK CONSTRAINT [CK_reservable_tables_1]
GO
```

### RESERVATIONS
Tabela przechowująca dane dotyczące rezerwacji
```sql
USE [u_cyra_1]
GO

/****** Object:  Table [dbo].[reservations]    Script Date: 24.12.2020 16:09:35 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[reservations](
	[reservation_id] [int] IDENTITY(1,1) NOT NULL,
	[customer_id] [int] NOT NULL,
	[table_id] [int] NOT NULL,
	[date_start_time] [datetime2](7) NOT NULL,
	[date_endtime] [datetime2](7) NOT NULL,
	[is_acepted] [int] NOT NULL,
 CONSTRAINT [PK_reservations] PRIMARY KEY CLUSTERED 
(
	[reservation_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservations]  WITH CHECK ADD  CONSTRAINT [FK_reservations_customers] FOREIGN KEY([customer_id])
REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[reservations] CHECK CONSTRAINT [FK_reservations_customers]
GO

ALTER TABLE [dbo].[reservations]  WITH CHECK ADD  CONSTRAINT [FK_reservations_reservable_tables] FOREIGN KEY([table_id])
REFERENCES [dbo].[reservable_tables] ([res_table_id])
GO

ALTER TABLE [dbo].[reservations] CHECK CONSTRAINT [FK_reservations_reservable_tables]
GO

ALTER TABLE [dbo].[reservations]  WITH CHECK ADD  CONSTRAINT [CK_reservations] CHECK  (([date_start_time]<[date_endtime]))
GO

ALTER TABLE [dbo].[reservations] CHECK CONSTRAINT [CK_reservations]
GO
```

### RESERVATIONS_COLLECTOR
Tabela przechowująca dane o osobach przypisanych do danej rezerwacji
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[reservations_collector](
	[reservation_id] [int] NOT NULL,
	[person_id] [int] NOT NULL,
 CONSTRAINT [PK_reservations_collector] PRIMARY KEY CLUSTERED 
(
	[reservation_id] ASC,
	[person_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservations_collector]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_collector_person] FOREIGN KEY([person_id])
	REFERENCES [dbo].[person] ([person_id])
GO

ALTER TABLE [dbo].[reservations_collector]
CHECK CONSTRAINT [FK_reservations_collector_person]
GO

ALTER TABLE [dbo].[reservations_collector]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_collector_reservations] FOREIGN KEY([reservation_id])
	REFERENCES [dbo].[reservations] ([reservation_id])
GO

ALTER TABLE [dbo].[reservations_collector]
CHECK CONSTRAINT [FK_reservations_collector_reservations]
GO
```

### RESERVATIONS_ORDERS
Tabela przechowująca infomacje o przypisaniu zamówień do rezerwacji
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[reservations_orders](
	[reservation_id] [int] NOT NULL,
	[order_id] [int] NOT NULL,
 CONSTRAINT [PK_reservations_orders] PRIMARY KEY CLUSTERED 
(
	[reservation_id] ASC,
	[order_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservations_orders]  WITH CHECK ADD  CONSTRAINT [FK_reservations_orders_orders] FOREIGN KEY([order_id])
REFERENCES [dbo].[orders] ([order_id])
GO

ALTER TABLE [dbo].[reservations_orders] CHECK CONSTRAINT [FK_reservations_orders_orders]
GO

ALTER TABLE [dbo].[reservations_orders]  WITH CHECK ADD  CONSTRAINT [FK_reservations_orders_reservations] FOREIGN KEY([reservation_id])
REFERENCES [dbo].[reservations] ([reservation_id])
GO

ALTER TABLE [dbo].[reservations_orders] CHECK CONSTRAINT [FK_reservations_orders_reservations]
GO
```

### STATUS_DICTIONARY
Słownik statusów, w których może znajdować się zamówienie
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[status_dictionary](
	[status_id] [int] IDENTITY(1,1) NOT NULL,
	[status_name] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_status_dictionary] PRIMARY KEY CLUSTERED 
(
	[status_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```

### TABLES
Tabela przechowująca informacje o stolikach, które znajdują się na stanie.
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[tables](
	[table_id] [int] IDENTITY(1,1) NOT NULL,
	[max_seats_no] [int] NOT NULL,
 CONSTRAINT [PK_tables] PRIMARY KEY CLUSTERED 
(
	[table_id] ASC
)WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
