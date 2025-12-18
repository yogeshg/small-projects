# Simulation and plot using matplotlib (not seaborn, per environment rules)

import matplotlib.pyplot as plt

ages = list(range(1, 101))

def simulate(
        childhood_age = 15,
        college_age = 20,
        retirement_age = 65,
        childhood_expense = 5000,
        college_expense = 15000,
        working_expense = 30000,
        retirement_expense = 20000,
        working_income = 40000,
        growth_rate = 0.025
):
    expenses = []
    income = []
    assets = []
    liabilities = []

    savings = 0.0
    debt = 0.0

    for age in ages:
        if age < childhood_age:
            yearly_expense = childhood_expense
            yearly_income = yearly_expense  # bank of mom and dad

        elif age < college_age:
            yearly_expense = college_expense
            yearly_income = 0

        elif age < retirement_age:
            yearly_expense = working_expense
            yearly_income = working_income

        else:  # retirement
            yearly_expense = retirement_expense
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


USD_FORMATTER = plt.FuncFormatter(lambda x, _: f'${int(x):,}')


def plot():
    expenses, income, assets, liabilities = simulate()

    # Plot
    _, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(10, 6), sharex=True, sharey=True)

    ax1.set_yscale("log")
    ax1.set_ylim(ymin=1000, ymax=1_000_000)
    ax1.yaxis.set_major_formatter(USD_FORMATTER)

    plot_income(ax1, income)
    plot_expenses(ax2, expenses)
    plot_assets(ax3, assets)
    plot_liabilities(ax4, liabilities)


    plt.tight_layout()
    plt.savefig("plot_income_expenses_assets_liabilities_log.png")

    # add a single, non-log plot for assets
    fig, ax = plt.subplots(figsize=(8, 4))
    ax.set_ylim(ymin=1000, ymax=1_000_000)
    ax.yaxis.set_major_formatter(USD_FORMATTER)
    plot_assets(ax, assets)
    ax.set_ylabel("Amount (linear scale)")
    plt.tight_layout()
    plt.savefig("plot_assets_linear.png")


def plot_income(ax, income):
    ax.bar(ages, income, label="Income", alpha=0.5, color="tab:green", width=1)
    ax.set_ylabel("Amount")
    ax.set_title("Income Over Life")
    for age in [7, 45, 80]:
        ax.text(age, income[age-1] + 2000, f'${income[age-1]:,}', ha='center')
    ax.legend()


def plot_expenses(ax, expenses):
    ax.bar(ages, expenses, label="Expenses", alpha=0.5, color="tab:red", width=1)
    ax.set_ylabel("Amount")
    ax.set_title("Expenses Over Life")
    for age in [7, 18, 45, 80]:
        ax.text(age, expenses[age-1] + 2000, f'${expenses[age-1]:,}', ha='center')
    ax.legend()


def plot_assets(ax, assets):
    ax.bar(ages, assets, label="Assets (Savings)", alpha=0.5, color="tab:blue", width=1)
    ax.set_ylabel("Amount (log scale)")
    ax.set_xlabel("Age")
    ax.set_title("Assets Over Life")
    for age in [27, 45, 65, 85]:
        ax.text(age, assets[age-1] * 1.2, f'${int(assets[age-1]):,}', ha='center')
    ax.legend()


def plot_liabilities(ax, liabilities):
    ax.bar(ages, liabilities, label="Liabilities (Debt)", alpha=0.5, color="tab:orange", width=1)
    ax.set_ylabel("Amount (log scale)")
    ax.set_xlabel("Age")
    ax.set_title("Liabilities Over Life")
    for age in [19, 26]:
        ax.text(age, liabilities[age-1] * 1.2, f'${int(liabilities[age-1]):,}', ha='center')
    ax.legend()


if __name__ == "__main__":
    plot()