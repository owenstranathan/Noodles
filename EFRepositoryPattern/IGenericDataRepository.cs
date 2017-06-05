// TUTORIAL
// This is a generic Data Access layer that uses Entity Framework
// It impliments the Repository Pattern
// described here (http://www.asp.net/mvc/overview/older-versions/getting-started-with-ef-5-using-mvc-4/implementing-the-repository-and-unit-of-work-patterns-in-an-asp-net-mvc-application)
// And again here (https://blog.magnusmontin.net/2013/05/30/generic-dal-using-entity-framework/)
// And once more here (https://msdn.microsoft.com/en-us/library/ff649690.aspx)
// And MOST IMPORTANTLY here (http://www.codeproject.com/Articles/207820/The-Repository-Pattern-with-EF-code-first-Dependen)
// There are several key aspects to the repository pattern, they are:
//
//		GenericRepository
//			Generically impliments the key CRUD functions to be used in each repository
//			Provides the base behavior for the repositories (described below)
//
//		UnitOfWork
//			Impliments the functionality (such as SaveChanges) responsible for doing the
//			"work" (i.e. actually saveing any creations, updates and deletions to the Database)
//			It is called a "Unit" of "work" because rather than doing all the work each time the
//			Logic makes a call, it stores changes and persists them to the database at one time as a "Unit"
//			NOTE: Presently, the UnitOfWork pattern is not true in effect as each call to a Repository, persists the changes therein.
//				  Remove calls to context.SaveChanges() with in the GenericDataRepository class to correct.
//
//		IndividualRepositories
//			Acts as a data mapping between the Database and the logic, Where changes are made to values in the database, stored by the repositories
//			And persisted by the UnitOfWork
//
// Our implimentation:
//
//		class GenericDataRepository:
//			our GenericDataRepository class fullfills the role of the GenerucRepository (described above) and is the Base class of all
//			Repositories.
//
//			It is a Generic class which takes 2 Generic Type parameters TDbContext and TDbSet:
//				TDbContext - the type of the EntityFramework DbContext used by the Repository inheriting from GenericDataRepository
//				TDbSet - the type of the EntityFramework DbSet that the repository inheriting from GenericDataRepository impliments
//
//			Methods:
//				Create:
//					Add(item): Adds an entity to the context
//				Retrieve:
//					GetAll(): Retrieves all data from the context.
//					GetWhere(predicate): Retrieves all data from the context on the given predicate
//					GetFirstOrDefault(predicate): Retrieves first data from the context on the given predicate or null
//				Update:
//					Handled by UnitOfWork when context is shared, (unshared non-tracking context is currently unsupported)
//				Delete:
//					Remove(item): Removes given item from the context
//					RemoveAll(): Removes all data from the context
//					RemoveWhere(predicate): Removes data from the context on the give predicate
//					RemoveFirstOrDefault(predicate): Removes first data from the context on the given predicate or does nothing
//
//
//
//		interface IUnitOFWork:
//			In our implimentation we only need SaveChanges, but if you need anyother UW functionality you would put it in this interface
//			and then impliment it in your DataAccessContext class which needs to inherit from IUnitOfWork
//
//
// Example:
//		Suppose that we have an EF DbContext type called DB and it contains DbSet types Users, Purchases and Products that correspond to tables in out actual
//		Database, using our GenericDataAccessLayer makes creating a DataAccessLayer quick and removes redundant code.
//	Code:
//
//		public class DALContext : IUnitOfWork
//		{
//
//			public DALContext()
//			{
//				context = new DB();
//				Users = new UserRepository();
//				Purchases = new PurchaseRepository();
//				Products = new ProductRepository();
//			}
//
//			private DbContext context;
//
//
//			internal UserRepository Users;
//			internal PurchaseRepository Purchases;
//			internal ProductRepository Products;
//
//			public int SaveChanges()
//			{
//				return context.SaveChanges();
//			}
//		}
//
//		public class UserRepository : GenericDataRepository<DB, Users>
//		{
//			public UserRepository(DB db) : base(db) { }
//		}
//
//		public class PurchaseRepository : GenericDataRepository<DB, Purchases>
//		{
//			public PurchaseRepository(DB db) : base(db) { }
//		}
//
//		public class ProductRepository : GenericDataRepository<DB, Products>
//		{
//			public ProductRepository(DB db) : base(db) { }
//		}
//
// The in your logic to use it you do something like this
//
//		DALContext context = new DALContext();
//		var User = context.Users.GetFirstOrDefault(x => x.id == 1);
//		var UserPurchases = context.Purchases.GetWhere(x => x.UserId = User.id);
//		var UserProducts = context.Products.GetWhere(x => UserPurchases.Select(y => y.ProductId).Contains(x.ProductId));
//
// this is a very simple example, and it makes the assumption that there are no managed relationships between Users, Purchases and Products
// but what if the schema looks like this
//
// USERS:
//	  ID INT PRIMARY_KEY;
//
// PRODUCT
//	  ID INT PRIMARY_KEY;
//
// PURCHASES:
//	  ID INT PRIMARY_KEY;
//	  USER_ID INT FOREIGN_KEY(USERS);
//	  PRODUCT_ID INT FOREIGN_KEY(PRODUCTS);
//
// Then our EF model is likely to have some navigation properties associated with Purchases
// It will probably look like this:
//
//		class Purchase : DbSet
//		{
//			int Id;
//			User User;
//			List<Product> Products;
//		}
//
// So we can get all the data we got with
// 3 DAL calls with one call
//
//		var UserPurchases = context.Purchases.GetWhere(x => UserId = 1, x => x.Users, x => x.Products)
//
// this will retrieve all the Purchases for User with id == 1 and attach the user and product to the purchase
// So in order to get the user for the purchase you do:
//
//		var User = UserPurchases[0].User;
//
// And to get the products for a purchase
//
//		var PurchaseProducts = UserPurchases[0].Products;
//
// And there you have it, a simple DAL for your project up and running in minutes.

namespace RepositoryPattern
{
    public interface IGenericDataRepository<TDatabase, TDbSet>
        where TDbSet : DbSet
        where TDatabase : DbContext
    {

        int Add(params T[] items);

        IList<T> GetAll(params Expression<Func<T, object>>[] navigationProperties);

        IList<T> GetWhere(Func<T, bool> where, params Expression<Func<T, object>>[] navigationProperties);

        T GetFirstOrDefault(Func<T, bool> where = null, params Expression<Func<T, object>>[] navigationProperties);

        int Remove(params T[] items);

        int Remove(IList<T> items);

        int RemoveAll();

        int RemoveWhere(Func<T, bool> where);

        int RemoveFirstOrDefault(Func<T, bool> where);

    }
}
