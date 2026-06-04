import java.util.concurrent.Semaphore;

class Account {

    String name;
    int balance;

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Bank {

    static Semaphore mutex = new Semaphore(1);

    static void transfer(Account from,
                         Account to,
                         int amount) {

        try {

            mutex.acquire();

            try {

                Thread.sleep(500);

                from.balance -= amount;
                to.balance += amount;

                System.out.println(
                        Thread.currentThread().getName()
                        + " transferred "
                        + amount
                        + " from "
                        + from.name
                        + " to "
                        + to.name
                );

            } finally {

                mutex.release();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

public class DeadlockFixed {

    public static void main(String[] args)
            throws Exception {

        Account A = new Account("A", 1000);
        Account B = new Account("B", 1000);

        int startingTotal = A.balance + B.balance;

        System.out.println(
                "Starting total: " + startingTotal
        );

        Thread t1 = new Thread(
                () -> Bank.transfer(A, B, 100),
                "Worker 1"
        );

        Thread t2 = new Thread(
                () -> Bank.transfer(B, A, 200),
                "Worker 2"
        );

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        int finalTotal = A.balance + B.balance;

        System.out.println("\nFinal A: " + A.balance);
        System.out.println("Final B: " + B.balance);

        System.out.println(
                "Final total: " + finalTotal
        );

        System.out.println(
                "No deadlock occurred"
        );
    }
}
