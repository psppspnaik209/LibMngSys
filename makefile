a.exe: main.o Book.o Patron.o Loan.o PatronCollection.o LoanCollection.o AudioCD.o BookChild.o DVD.o LibraryItem.o LibraryItemCollection.o
	g++ main.o Book.o Patron.o Loan.o PatronCollection.o LoanCollection.o AudioCD.o BookChild.o DVD.o LibraryItem.o LibraryItemCollection.o

main.o: main.cpp Book.h Patron.h Loan.h PatronCollection.h LoanCollection.h
	g++ -c main.cpp

Book.o: Book.cpp Book.h
	g++ -c Book.cpp

Patron.o: Patron.cpp Patron.h
	g++ -c Patron.cpp

Loan.o: Loan.cpp Loan.h Book.h Patron.h
	g++ -c Loan.cpp

PatronCollection.o: PatronCollection.cpp PatronCollection.h Patron.h
	g++ -c PatronCollection.cpp

LoanCollection.o: LoanCollection.cpp LoanCollection.h Loan.h
	g++ -c LoanCollection.cpp

AudioCD.o: AudioCD.cpp AudioCD.h LibraryItem.h
	g++ -c AudioCD.cpp

BookChild.o: BookChild.cpp BookChild.h LibraryItem.h
	g++ -c BookChild.cpp

DVD.o: DVD.cpp DVD.h LibraryItem.h
	g++ -c DVD.cpp

LibraryItem.o: LibraryItem.cpp LibraryItem.h
	g++ -c LibraryItem.cpp

LibraryItemCollection.o: LibraryItemCollection.cpp LibraryItemCollection.h LibraryItem.h
	g++ -c LibraryItemCollection.cpp
