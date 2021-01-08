# Opisy tabel

[Address](tableDescriptions.md#address) | [Categories](tableDescriptions.md#categories) | [Cities](tableDescriptions.md#cities) | [Companies](tableDescriptions.md#companies) | [Companies Employees](tableDescriptions.md#companies_employees) |
:---: | :---: | :---: | :---: | :---: |
[**Countries**](tableDescriptions.md#countries) | [**Customers**](tableDescriptions.md#customers) | [**Customers Discounts**](tableDescriptions.md#customers_discounts) | [**Discount Data**](tableDescriptions.md#discount_data) | [**Discount Data In Programs**](tableDescriptions.md#dicount_data_in_programs) |
[**Employees**](tableDescriptions.md#employees) | [**Individual**](tableDescriptions.md#individual) | [**Menu**](tableDescriptions.md#menu) | [**Menu Details**](tableDescriptions.md#menu_details) | [**Menu Items**](tableDescriptions.md#menu_items) |
[**Order Details**](tableDescriptions.md#order_details) | [**Orders**](tableDescriptions.md#orders) | [**Person**](tableDescriptions.md#person) | [**Programs**](tableDescriptions.md#programs) | [**Reservable Tables**](tableDescriptions.md#reservable_tables) |
[**Reservations**](tableDescriptions.md#reservations) | [**Reservations Collector**](tableDescriptions.md#reservations_collector) | [**Reservations Orders**](tableDescriptions.md#reservations_orders) | [**Status Dictionary**](tableDescriptions.md#status_dictionary) | [**Tables**](tableDescriptions.md#tables) |
	
### ADDRESS
Tabela przechowująca dane o adresach osobowych i firmowych.


Każdy rekord zawiera identyfikator: `address_id`, który jest kluczem głównym tabeli.
Zawartość kolumny `street` to adres rozumiany jako ulica z przypisanym numerem domu lub/i mieszkania.
Dalej znajduje się kod pocztowy `postal_code`. Może on być postaci XX-XXX | XXXXXX | XXXXXXX, gdzie X jest cyfrą 0-9.
Ponadto klucz obcy `city_id` pozwala zidentyfikować miasto przypisane do adresu (tabela słownikowa [Cities](tableDescriptions.md#cities)).
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
	[postal_code] [nvarchar](10) NOT NULL,
	[city_id] [int] NOT NULL,

CONSTRAINT [PK_address] PRIMARY KEY CLUSTERED (
	[address_id] ASC)
WITH (PAD_INDEX = OFF,
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

ALTER TABLE [dbo].[address]
WITH CHECK ADD
	CONSTRAINT [CK_address_postal_code]
	CHECK (( [postal_code] LIKE '[0-9][0-9]-[0-9][0-9][0-9]'
		OR [postal_code] LIKE '[0-9][0-9][0-9][0-9][0-9][0-9]'
		OR [postal_code] LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9]' ))
		
ALTER TABLE [dbo].[address]
CHECK CONSTRAINT [CK_address_postal_code]
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### CATEGORIES
Tabela przechowująca dane o kategoriach potraw znajdujących się w menu (np. _owoce morza_).

Każda kategoria jest identyfikowana za pomocą klucza głównego: `category_id`. Nazwy kategorii są unikalne.
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

CONSTRAINT [PK_categories] PRIMARY KEY CLUSTERED (
	[category_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_category_name] UNIQUE NONCLUSTERED (
	[category_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### CITIES
Tabela przechowująca dane o miastach znajdujących się w bazie danych.

Miasta identyfikowane są za pomocą klucza głównego `city_id`, rekord zawiera także informację o nazwie miasta (`city_name`) oraz klucz obcy `country_id` wskazujący na rekord w tabeli słownikowej państw ([Countries](tableDescriptions.md#countries)), określający gdzie znajduje się dana miejscowość.

Nazwy miast są unikalne, mimo że w obrębie jednego państwa może znajdować się kilka miejscowości o tej samej nazwie, ponieważ tabela przechowuje tylko ich nazwy, nie służy do jednoznacznej identyfikacji. Ta ma miejsce o jeden krok "wyżej" w hierarchii: w tabeli [Address](tableDescriptions.md#address), gdzie przechowywany jest kod pocztowy (kod pocztowy nie jest przechowywany w tabeli miast, ponieważ czasami różni się w zależności od dzielnicy danego miasta).
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
	
CONSTRAINT [PK_cities] PRIMARY KEY CLUSTERED (
	[city_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_city_name] UNIQUE NONCLUSTERED (
	[city_name] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### COMPANIES
Tabela przechowująca dane o klientach firmowych: identyfikator firmy oraz klienta, nazwę firmy, adres, numer telefonu, email, NIP.

Warunki integralnościowe:
- numer klienta `customer_id` jest unikalny (połączenie 1-to-1 z tabelą [Customers](tableDescriptions.md#customers))
- adres: unikalny (połączenie 1-to-1 z tabelą [Address](tableDescriptions.md#address))
- email: unikalny, ponadto zawiera symbol '@' oraz po co najmniej jednym znaku (litera bądź cyfra) z każdej strony symbolu, nie może zawierać dwóch znaków '@', nie może zawierać spacji
- NIP (`NIP`): unikalny, 10 cyfr
- telefon (`phone`): unikalny, znaki numeryczne
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
	
CONSTRAINT [PK_companies] PRIMARY KEY CLUSTERED (
	[company_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_company_address] UNIQUE NONCLUSTERED (
	[address_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_customer_id] UNIQUE NONCLUSTERED (
	[customer_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_company_phone] UNIQUE NONCLUSTERED (
	[phone] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_company_email] UNIQUE NONCLUSTERED (
	[email] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_company_NIP] UNIQUE NONCLUSTERED (
	[NIP] ASC)
WITH (PAD_INDEX = OFF,
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

ALTER TABLE [dbo].[companies]
WITH CHECK ADD
	CONSTRAINT [CK_companies_phone_pattern]
	CHECK (( ISNUMERIC([phone])=1 ))

ALTER TABLE [dbo].[companies]
CHECK CONSTRAINT [CK_companies_phone_pattern]

ALTER TABLE [dbo].[companies]
WITH CHECK ADD
	CONSTRAINT [CK_companies_email_pattern]
	CHECK (( [email] LIKE '[a-z0-9]%@%[a-z0-9]'
		AND [email] NOT LIKE '%@%@%'
		AND [email] NOT LIKE '% %'))
GO

ALTER TABLE [dbo].[companies]
CHECK CONSTRAINT [CK_companies_email_pattern]
GO

ALTER TABLE [dbo].[companies]
WITH CHECK ADD
	CONSTRAINT [CK_companies_NIP_pattern]
	CHECK (( [NIP] LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]' ))
GO

ALTER TABLE [dbo].[companies]
CHECK CONSTRAINT [CK_companies_NIP_pattern]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### COMPANIES_EMPLOYEES
Tabela zawierająca informacje o pracownikach klientów firmowych. Klucz główny składa się z pary wartości: identyfikatora osoby oraz identyfikatora firmy.
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
	
 CONSTRAINT [PK_companies_employees] PRIMARY KEY CLUSTERED (
	[person_id] ASC,
	[company_id] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### COUNTRIES
Słownik (pary identfikator + nazwa) państw występujących w adresach osobowych i firmowych. Nazwy państw są unikalne.
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

CONSTRAINT [PK_countries] PRIMARY KEY CLUSTERED (
	[country_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_country_name] UNIQUE NONCLUSTERED (
	[country_name] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### CUSTOMERS
Tabela przechowująca ID klientów. Klient może być indywidualny lub firmowy. Szczegółowe informacje dotyczące klienta znajdują się wówczas odpowiednio w tabeli [Individual](tableDescriptions.md#individual) lub [Companies](tableDescriptions.md#companies)
```sql
USE [u_cyra_1]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[customers](
	[customer_id] [int] IDENTITY(1,1) NOT NULL,

CONSTRAINT [PK_customers] PRIMARY KEY CLUSTERED (
	[customer_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### CUSTOMERS_DISCOUNTS
Tabela przechowująca dane o programach rabatowych poszczególnych klientów. Na pojedynczy rekord w tabeli składa się identyfikator klienta, identyfikator programu oraz `date_start_time`: czas rozpoczęcia możliwości korzystania przez klienta ze zniżek przewidzianych w programie (niektóre programy są ograniczone czasowo). Defaultowo jest to moment tworzenia nowego rekordu.
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

CONSTRAINT [PK_customers_discounts] PRIMARY KEY CLUSTERED (
	[customer_id] ASC,
	[program_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[customers_discounts]
ADD
	CONSTRAINT [DF_date_start_time]
	DEFAULT (getdate()) FOR [date_start_time]
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### DISCOUNT_DATA
Tabela przechowująca dane dotyczące zmiennych występujących jako wartości liczbowe w poszczególnych programach rabatowych. Rekord składa się z danych przechowywanych w trzech kolumnach: identyfikator, typ (`type`) oraz wartość (`value`). Typ jest unikalny oraz jest postaci litera/y + liczba porządkowa, np. Z1, K1, K2, K2, FK1, FK2 itp.
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

CONSTRAINT [PK_discount_data] PRIMARY KEY CLUSTERED (
	[discount_data_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_discount_type] UNIQUE NONCLUSTERED (
	[type] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[discount_data]
WITH CHECK ADD
	CONSTRAINT [CK_discount_type_pattern]
	CHECK ([type] LIKE (( '[A-Z][0-9]' ))
		OR [type] LIKE (('[A-Z][A-Z][0-9]')) )
GO

ALTER TABLE [dbo].[discount_data]
CHECK CONSTRAINT [CK_discount_type_pattern]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

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
	
CONSTRAINT [PK_discount_data_in_programs] PRIMARY KEY CLUSTERED (
	[discount_data_id] ASC,
	[program_id] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

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

CONSTRAINT [PK_employees] PRIMARY KEY CLUSTERED (
	[employee_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### INDIVIDUAL
Tabela przechowująca dane o klientach indywidualnych. Rekord składa się z dwóch pól: identyfikatora osoby i identyfikatora klienta.
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
	
CONSTRAINT [PK_individual] PRIMARY KEY CLUSTERED (
	[person_id] ASC,
	[customer_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_individual_customer_ID] UNIQUE NONCLUSTERED (
	[customer_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
	
CONSTRAINT [UQ_individual_person_ID] UNIQUE NONCLUSTERED (
	[person_id] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### MENU
Tabela przechowująca dane o menu. Identyfikujemy je za pomocą klucza (`menu_id`), każde menu obowiązuje w wyznaczonych ramach czasowych: od `since_date` do `due_date`, `since_date`<`due_date`.
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
	
CONSTRAINT [PK_menu] PRIMARY KEY CLUSTERED (
	[menu_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[menu]
WITH CHECK ADD
	CONSTRAINT [CK_menu_dates]
	CHECK (( [since_date] < [due_date] ))
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### MENU_DETAILS
Tabela przechowująca informacje szczegółowe dotyczące poszczególnych menu. Rekord składa się z identyfikatora menu, identyfikatora pozycji menu, znacznika, czy dana pozycja jest aktualnie dostępna (domyślnie tak) oraz ceny jednostkowej danej pozycji. Dostępność pozycji jest opisana w kolumnie `is_available`, której wartości są {0, 1} są interpretowane jako {NIE, TAK}.
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
	
CONSTRAINT [PK_menu_details] PRIMARY KEY CLUSTERED (
	[menu_id] ASC,
	[item_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[menu_details]
ADD
	CONSTRAINT [DF_is_available]
	DEFAULT ( (1) ) FOR [is_available]
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

ALTER TABLE [dbo].[menu_details]
WITH CHECK ADD
	CONSTRAINT [CK_menu_is_available_value]
	CHECK (( [is_available] in (0, 1) ))
GO

ALTER TABLE [dbo].[menu_details]
CHECK CONSTRAINT [CK_menu_is_available_value]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### MENU_ITEMS
Tabela przechowująca dane dotyczące pojedynczych dań mogących występować w menu.
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
	
CONSTRAINT [PK_menu_items] PRIMARY KEY CLUSTERED (
	[item_id] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### ORDER_DETAILS
Tabela przechowująca szczegółowe informacje dotyczące zamówienia. Rekord zawiera identyfikator zamówienia, identyfikator zamówionej pozycji menu, jej cenę, ilość, oraz ewentualny rabat (domyślnie 0).
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
	
CONSTRAINT [PK_order_details] PRIMARY KEY CLUSTERED (
	[order_id] ASC,
	[item_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[order_details]
ADD
	CONSTRAINT [DF_item_discount]
	DEFAULT ( (0) ) FOR [item_discount]
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### ORDERS
Tabela przechowująca dane o składanych zamówieniach. Rekord składa się z identyfikatora zamówienia, identyfikatora klienta, identyfikatora pracownika obsługującego zamówienie, daty złożenia zamówienia i jego odbioru (warunek: `order_date`<`collection_date`) oraz statusu , w którym obecnie znajduje się zamówienie (tłumaczonego w słowniku [Status Dictionary](tableDescriptions.md#status_dictionary))
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
	
CONSTRAINT [PK_orders] PRIMARY KEY CLUSTERED (
	[order_id] ASC)
WITH (PAD_INDEX = OFF,
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

ALTER TABLE [dbo].[orders]
WITH CHECK ADD
	CONSTRAINT [CK_order_dates]
	CHECK (( [order_date]<[collection_date] ))
GO

ALTER TABLE [dbo].[orders]
CHECK CONSTRAINT [CK_order_dates]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### PERSON
Tabela przechowująca dane osobowe klientów indywidualnych, pracowników klientów firmowych oraz pracowników gastronomii. Na dane osobowe składa się: identyfikator osoby (klucz główny), imię, nazwisko, email, numer telefonu, adres.

Warunki integralnościowe:
- adres: unikalny (połączenie 1-to-1 z tabelą [Address](tableDescriptions.md#address))
- email: unikalny, ponadto zawiera symbol '@' oraz po co najmniej jednym znaku (litera bądź cyfra) z każdej strony symbolu, nie może zawierać dwóch znaków '@', nie może zawierać spacji
- telefon: unikalny, znaki numeryczne
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

CONSTRAINT [PK_person] PRIMARY KEY CLUSTERED (
	[person_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_personal_address] UNIQUE NONCLUSTERED (
	[address_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_personal_email] UNIQUE NONCLUSTERED (
	[email] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_personal_phone] UNIQUE NONCLUSTERED (
	[phone] ASC)
WITH (PAD_INDEX = OFF,
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
	CONSTRAINT [CK_personal_email_pattern]
	CHECK (([email] like '[a-z0-9]%@%[a-z0-9]'
		AND NOT [email] like '%@%@%'
		AND NOT [email] like '% %'))
GO

ALTER TABLE [dbo].[person]
CHECK CONSTRAINT [CK_personal_email_pattern]
GO

ALTER TABLE [dbo].[person]
WITH CHECK ADD
	CONSTRAINT [CK_personal_phone_pattern]
	CHECK ((ISNUMERIC([phone])=(1)))
GO

ALTER TABLE [dbo].[person]
CHECK CONSTRAINT [CK_personal_phone_pattern]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### PROGRAMS
Tabela przechowująca dane o programach rabatowych. Rekord składa się z identyfikatora (klucza głównego) oraz opisu programu rabatowego, wyświetlanego np. w ramach informacji dla klientów.
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

CONSTRAINT [PK_programs] PRIMARY KEY CLUSTERED (
	[program_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### RESERVABLE_TABLES
Tabela przechowująca dane dotyczące stolików, które można rezerwować. Ograniczenia dotyczące danego stolika obowiązują w czasie `since_date` do `due_date`, `since_date`<`due_date`. Wymagamy, aby liczba miejsc przy stoliku była większa od zera, stoliki których nie można rezerwować nie są przechowywane w tej tabeli.
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

CONSTRAINT [PK_reservable_tables] PRIMARY KEY CLUSTERED (
	[res_table_id] ASC)
WITH (PAD_INDEX = OFF,
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
	CONSTRAINT [CK_reservable_seats_no]
	CHECK (( [seats_no] > (0) ))
GO

ALTER TABLE [dbo].[reservable_tables]
CHECK CONSTRAINT [CK_reservable_seats_no]
GO

ALTER TABLE [dbo].[reservable_tables]
WITH CHECK ADD
	CONSTRAINT [CK_reservable_tables_dates]
	CHECK (( [since_date]<[due_date] ))
GO

ALTER TABLE [dbo].[reservable_tables]
CHECK CONSTRAINT [CK_reservable_tables_dates]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### RESERVATIONS
Tabela przechowująca dane dotyczące rezerwacji. Rekord składa się z identyfikatora rezerwacji (klucz główny), identyfikatora klienta, identyfikatora stolika, dat od kiedy do kiedy zarezerwowano stolik (warunek: `date_start_time`<`date_end_time`) oraz informacji o tym, czy rezerwacja została zaakceptowana przez obsługę (`is_accepted`). Pole `is_accepted` przechowuje wartości liczbowe {0, 1} interpretowane jako {NIE, TAK}. Domyślna wartość tego pola to 0 (przed akceptacją przez obsługę).
```sql
USE [u_cyra_1]
GO

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
	[is_accepted] [int] NOT NULL,
	
CONSTRAINT [PK_reservations] PRIMARY KEY CLUSTERED(
	[reservation_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservations]
ADD
	CONSTRAINT [DF_is_accepted]
	DEFAULT ( (0) ) FOR [is_accepted]
GO

ALTER TABLE [dbo].[reservations]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_customers] FOREIGN KEY([customer_id])
	REFERENCES [dbo].[customers] ([customer_id])
GO

ALTER TABLE [dbo].[reservations]
CHECK CONSTRAINT [FK_reservations_customers]
GO

ALTER TABLE [dbo].[reservations]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_reservable_tables] FOREIGN KEY([table_id])
	REFERENCES [dbo].[reservable_tables] ([res_table_id])
GO

ALTER TABLE [dbo].[reservations]
CHECK CONSTRAINT [FK_reservations_reservable_tables]
GO

ALTER TABLE [dbo].[reservations]
WITH CHECK ADD
	CONSTRAINT [CK_reservations_date_check]
	CHECK (( [date_start_time] < [date_endtime] ))
GO

ALTER TABLE [dbo].[reservations]
CHECK CONSTRAINT [CK_reservations_date_check]
GO

ALTER TABLE [dbo].[reservations]
WITH CHECK ADD
	CONSTRAINT [CK_reservations_is_accepted_value]
	CHECK (( [is_accepted] in (0, 1) ))
GO

ALTER TABLE [dbo].[reservations]
CHECK CONSTRAINT [CK_reservations_is_accepted_value]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### RESERVATIONS_COLLECTOR
Tabela przechowująca dane o osobach przypisanych do danej rezerwacji.
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
	
CONSTRAINT [PK_reservations_collector] PRIMARY KEY CLUSTERED (
	[reservation_id] ASC,
	[person_id] ASC)
WITH (PAD_INDEX = OFF,
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
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### RESERVATIONS_ORDERS
Tabela przechowująca infomacje o przypisaniu zamówień do rezerwacji. Przechowuje pary identyfikatorów: rezerwacja-zamówienie.
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
	
CONSTRAINT [PK_reservations_orders] PRIMARY KEY CLUSTERED (
	[reservation_id] ASC,
	[order_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[reservations_orders]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_orders_orders] FOREIGN KEY([order_id])
	REFERENCES [dbo].[orders] ([order_id])
GO

ALTER TABLE [dbo].[reservations_orders]
CHECK CONSTRAINT [FK_reservations_orders_orders]
GO

ALTER TABLE [dbo].[reservations_orders]
WITH CHECK ADD
	CONSTRAINT [FK_reservations_orders_reservations] FOREIGN KEY([reservation_id])
	REFERENCES [dbo].[reservations] ([reservation_id])
GO

ALTER TABLE [dbo].[reservations_orders]
CHECK CONSTRAINT [FK_reservations_orders_reservations]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### STATUS_DICTIONARY
Słownik (pary identyfikator + nazwa) statusów, w których może znajdować się zamówienie. Nazwy statusów są unikalne.
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

CONSTRAINT [PK_status_dictionary] PRIMARY KEY CLUSTERED (
	[status_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],

CONSTRAINT [UQ_status_name] UNIQUE NONCLUSTERED (
	[status_name] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)

### TABLES
Tabela przechowująca informacje o stolikach, które znajdują się na stanie. Rekord składa się z identyfikatora stolika (klucz główny `table_id`) orz maksymalnej liczby miejsc przy stoliku (liczba >0).
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

CONSTRAINT [PK_tables] PRIMARY KEY CLUSTERED (
	[table_id] ASC)
WITH (PAD_INDEX = OFF,
	STATISTICS_NORECOMPUTE = OFF,
	IGNORE_DUP_KEY = OFF,
	ALLOW_ROW_LOCKS = ON,
	ALLOW_PAGE_LOCKS = ON,
	OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[tables]
WITH CHECK ADD
	CONSTRAINT [CK_table_max_seats_no]
	CHECK (( [max_seats_no] > (0) ))
GO

ALTER TABLE [dbo].[tables]
CHECK CONSTRAINT [CK_table_max_seats_no]
GO
```
[:arrow_double_up:](tableDescriptions.md#opisy-tabel)
