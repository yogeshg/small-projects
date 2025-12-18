# Simulation and plot using matplotlib (not seaborn, per environment rules)

import matplotlib.pyplot as plt

ages = list(range(1, 101))

def simulate():
    expenses = []
    income = []
    assets = []
    liabilities = []

    savings = 0.0
    debt = 0.0
    growth_rate = 0.02

    for age in ages:
        # Identify phase
        if age < 15:  # childhood
            yearly_expense = 5000
            yearly_income = yearly_expense  # bank of mom and dad

        elif age < 20:  # college
            yearly_expense = 15000
            yearly_income = 0

        elif age < 65:  # working
            yearly_expense = 30000
            yearly_income = 40000

        else:  # retirement
            yearly_expense = 20000
            yearly_income = 0  # draw from assets

        surplus = yearly_income - yearly_expense
        # Apply investment growth
        savings *= (1 + growth_rate)

        # Apply surplus/deficit
        if debt > 0 and surplus > 0:
            payment = min(debt, surplus)
            debt -= payment
            surplus -= payment

        savings += surplus
        if savings < 0:
            debt += -savings
            savings = 0

        # if age % 2 == 0:
        #     print(f"Age {age}: Expense={yearly_expense}, Income={yearly_income}, Savings={savings:.2f}, Debt={debt:.2f}")

        expenses.append(yearly_expense)
        income.append(yearly_income)
        assets.append(max(savings, 1))      # avoid log(0)
        liabilities.append(max(debt, 1))    # avoid log(0)
    return expenses, income, assets, liabilities


def plot():
    expenses, income, assets, liabilities = simulate()

    # Plot
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(12, 8), sharex=True, sharey=True)

    ax1.set_yscale("log")
    ax1.set_ylim(ymin=1000, ymax=1_000_000)
    ax1.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'${int(x):,}'))

    plot_income(ax1, income)
    plot_expenses(ax2, expenses)
    plot_assets(ax3, assets)
    plot_liabilities(ax4, liabilities)


    plt.tight_layout()
    plt.savefig("plot.png")


def plot_income(ax, income):
    ax.bar(ages, income, label="Income", alpha=0.7, color="tab:green")
    ax.set_ylabel("Amount")
    ax.set_title("Income Over Life")
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'${int(x):,}'))
    ax.legend()


def plot_expenses(ax, expenses):
    ax.bar(ages, expenses, label="Expenses", alpha=0.7, color="tab:red")
    ax.set_ylabel("Amount")
    ax.set_title("Expenses Over Life")
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'${int(x):,}'))
    ax.legend()


def plot_assets(ax, assets):
    ax.bar(ages, assets, label="Assets (Savings)", alpha=0.7, color="tab:blue")
    ax.set_ylabel("Amount (log scale)")
    ax.set_xlabel("Age")
    ax.set_title("Assets Over Life")
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'${int(x):,}'))
    ax.legend()


def plot_liabilities(ax, liabilities):
    ax.bar(ages, liabilities, label="Liabilities (Debt)", alpha=0.7, color="tab:orange")
    ax.set_ylabel("Amount (log scale)")
    ax.set_xlabel("Age")
    ax.set_title("Liabilities Over Life")
    ax.legend()


if __name__ == "__main__":
    plot()