// Native contextual action exposed by the Job Board's ActionsManagerComponent.
class ECRP_AcceptDeliveryDriverAction : ScriptedUserAction
{
	protected static const float MAXIMUM_DISTANCE = 3.0;
	protected static const string DELIVERY_DRIVER_JOB_ID = "delivery_driver";
	protected static const ResourceName DELIVERY_PACKAGE_PREFAB =
		"{BBA21E130F0D45C7}Prefabs/Gameplay/Jobs/ECRP_DeliveryPackage.et";
	protected static const ResourceName DELIVERY_DESTINATION_PREFAB =
		"{D57BCE8D84F3742A}Prefabs/Gameplay/Jobs/ECRP_DeliveryDestination.et";

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);

		if (!character)
		{
			Print("ECRP: Delivery Driver job assignment failed: user is not a character.", LogLevel.ERROR);
			return;
		}

		ECRP_PlayerJobComponent jobComponent = ECRP_PlayerJobComponent.Cast(
			character.FindComponent(ECRP_PlayerJobComponent)
		);

		if (!jobComponent)
		{
			Print("ECRP: Delivery Driver job assignment failed: player job component is missing.", LogLevel.ERROR);
			return;
		}

		if (jobComponent.HasActiveJob())
		{
			Print("ECRP: Player already has an active job.", LogLevel.NORMAL);
			return;
		}

		if (!jobComponent.AssignJob(DELIVERY_DRIVER_JOB_ID))
		{
			Print("ECRP: Delivery Driver job assignment failed.", LogLevel.ERROR);
			return;
		}

		IEntity packageEntity = SpawnDeliveryPackage(pOwnerEntity);

		if (!packageEntity)
		{
			jobComponent.ClearActiveJob();
			Print("ECRP: Delivery Driver job assignment failed.", LogLevel.ERROR);
			return;
		}

		IEntity destinationEntity = SpawnDeliveryDestination(pOwnerEntity);

		if (!destinationEntity)
		{
			SCR_EntityHelper.DeleteEntityAndChildren(packageEntity);
			jobComponent.ClearActiveJob();
			Print("ECRP: Delivery Driver job assignment failed: delivery destination could not be spawned.", LogLevel.ERROR);
			return;
		}

		Print("ECRP: Delivery Driver job assigned.", LogLevel.NORMAL);
	}

	protected IEntity SpawnDeliveryPackage(IEntity jobBoard)
	{
		if (!jobBoard)
			return null;

		Resource packageResource = Resource.Load(DELIVERY_PACKAGE_PREFAB);

		if (!packageResource || !packageResource.IsValid())
		{
			Print("ECRP: Delivery package prefab could not be loaded.", LogLevel.ERROR);
			return null;
		}

		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;
		jobBoard.GetTransform(spawnParams.Transform);
		spawnParams.Transform[3] = jobBoard.CoordToParent("0 0 1.5");

		IEntity packageEntity = GetGame().SpawnEntityPrefab(
			packageResource,
			jobBoard.GetWorld(),
			spawnParams
		);

		if (!packageEntity)
		{
			Print("ECRP: Delivery package could not be spawned.", LogLevel.ERROR);
			return null;
		}

		Print("ECRP: Delivery package spawned.", LogLevel.NORMAL);
		return packageEntity;
	}

	protected IEntity SpawnDeliveryDestination(IEntity jobBoard)
	{
		if (!jobBoard)
			return null;

		Resource destinationResource = Resource.Load(DELIVERY_DESTINATION_PREFAB);

		if (!destinationResource || !destinationResource.IsValid())
		{
			Print("ECRP: Delivery destination prefab could not be loaded.", LogLevel.ERROR);
			return null;
		}

		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;
		jobBoard.GetTransform(spawnParams.Transform);
		spawnParams.Transform[3] = jobBoard.CoordToParent("20 0 0");

		IEntity destinationEntity = GetGame().SpawnEntityPrefab(
			destinationResource,
			jobBoard.GetWorld(),
			spawnParams
		);

		if (!destinationEntity)
		{
			Print("ECRP: Delivery destination could not be spawned.", LogLevel.ERROR);
			return null;
		}

		Print("ECRP: Delivery destination spawned.", LogLevel.NORMAL);
		return destinationEntity;
	}

	override bool CanBeShownScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool CanBePerformedScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		outName = "Accept Delivery Driver Job";
		return true;
	}

	protected bool IsUserInRange(IEntity user)
	{
		IEntity owner = GetOwner();

		if (!owner || !user)
			return false;

		return vector.Distance(owner.GetOrigin(), user.GetOrigin()) <= MAXIMUM_DISTANCE;
	}
}
