
namespace RepositoryPattern
{
    public class GenericDataRepository<TDbContext, TDbSet> : IGenericDataRepository<TDbContext, TDbSet>
		where TDbSet : class
		where TDbContext : DbContext
	{
		private GenericDataRepository() { }
		public GenericDataRepository(TDbContext db)
		{
			context = db;
		}

		protected TDbContext context;

        // unimplimented, make more code to be better!
		protected int ProcessEFException(Exception exception)
		{
			OracleException oracleException = exception as OracleException;
			DbEntityValidationException entityValidationException = exception as DbEntityValidationException;
			DbUpdateConcurrencyException updateConcurrencyException = exception as DbUpdateConcurrencyException;

			if (oracleException != null)
			{
				// Do Shit
			}
			else if (entityValidationException != null)
			{
                // Do Shit
			}
			else if (updateConcurrencyException != null)
			{
				// Do Shit
			}
			else if (exception.InnerException != null)
			{
				// dig into the InnerException
				return ProcessEFException(exception.InnerException);
			}
			else
			{
				// Do Shit
			}
			return Database.DontBeStupid;
		}


		/// <summary>
		/// Add(params T[] items) takes a list of arguments of type T and adds them to the associated DbSet
		/// i.e. DataRepository.Add(item1, item2, ...);
		/// </summary>
		/// <param name="items"></param>
		public virtual int Add(params TDbSet[] items)
		{
			try
			{
				var dbSet = context.Set<TDbSet>();

				foreach (TDbSet item in items)
				{
					dbSet.Add(item);
				}

				context.SaveChanges();
				return Database.Succeeded;
			}
			catch(Exception ex)
			{
				return ProcessEFException(ex);
			}
		}



		/// <summary>
		/// GetAll() returns all the elements in a Data Repository as an IList
		/// With the specified navagation properties associated to each elemet attached
		/// </summary>
		/// <param name="navigationProperties"></param>
		/// <returns></returns>
		public virtual IList<TDbSet> GetAll(params Expression<Func<TDbSet, object>>[] navigationProperties)
		{
			List<TDbSet> list;
			try
			{
				IQueryable<TDbSet> dbQuery = context.Set<TDbSet>();

				//Apply eager loading
				foreach (Expression<Func<TDbSet, object>> navigationProperty in navigationProperties)
				{
					dbQuery = dbQuery.Include<TDbSet, object>(navigationProperty);
				}

				list = dbQuery.ToList<TDbSet>();
			}
			catch(Exception ex)
			{
				ProcessEFException(ex);
				list = new List<TDbSet>();
			}

			return list;
		}

		/// <summary>
		/// Returns all items in a DataRespository that meet the condition specified in the 'where' Function argument,
		/// with any specified navigation properties attached where associated.
		/// </summary>
		/// <param name="where"></param>
		/// <param name="navigationProperties"></param>
		/// <returns>IList</returns>
		public virtual IList<TDbSet> GetWhere(Func<TDbSet, bool> where, params Expression<Func<TDbSet, object>>[] navigationProperties)
		{
			List<TDbSet> list;

			try
			{
				IQueryable<TDbSet> dbQuery = context.Set<TDbSet>();

				//Apply eager loading
				foreach (Expression<Func<TDbSet, object>> navigationProperty in navigationProperties)
					dbQuery = dbQuery.Include<TDbSet, object>(navigationProperty);

				list = dbQuery
					   .Where(where)
					   .ToList<TDbSet>();
			}
			catch(Exception ex)
			{
				ProcessEFException(ex);
				list = new List<TDbSet>();
			}

			return list;
		}

		/// <summary>
		/// Returns the first instance or null from a Data repository that matches the condition specified in the 'where' Function argument,
		/// with any specified navigation properties attached where associated.
		/// </summary>
		/// <param name="where"></param>
		/// <param name="navigationProperties"></param>
		/// <returns> T or null </returns>
		public virtual TDbSet GetFirstOrDefault(Func<TDbSet, bool> where = null, params Expression<Func<TDbSet, object>>[] navigationProperties)
		{
			TDbSet item = null;
			try
			{
				IQueryable<TDbSet> dbQuery = context.Set<TDbSet>();

				//Apply eager loading
				foreach (Expression<Func<TDbSet, object>> navigationProperty in navigationProperties)
					dbQuery = dbQuery.Include<TDbSet, object>(navigationProperty);

				if (where == null)
				{
					item = dbQuery.FirstOrDefault();
				}
				else
				{
					//Apply where clause
					item = dbQuery.FirstOrDefault(where);
				}
			}
			catch (Exception ex)
			{
				ProcessEFException(ex);
			}

			return item;
		}


		public virtual int Remove(params TDbSet[] items)
		{
			try
			{
				var dbSet = context.Set<TDbSet>();

				foreach (TDbSet item in items)
				{
					dbSet.Remove(item);
				}

				context.SaveChanges();
				return Database.Succeeded;
			}
			catch (Exception ex)
			{
				return ProcessEFException(ex);
			}
		}

		public virtual int Remove(IList<TDbSet> items)
		{
			return Remove(items.ToArray());
		}

		public virtual int RemoveAll()
		{
			return Remove(GetAll());
		}

		public virtual int RemoveWhere(Func<TDbSet, bool> where)
		{
			return Remove(GetWhere(where));
		}

		public virtual int RemoveFirstOrDefault(Func<TDbSet, bool> where)
		{
			return Remove(GetFirstOrDefault(where));
		}
	}
}
