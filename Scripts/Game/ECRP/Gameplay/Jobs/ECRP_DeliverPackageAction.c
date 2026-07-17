// Native contextual action exposed by the delivery destination's ActionsManagerComponent.
class ECRP_DeliverPackageAction : ScriptedUserAction
{
	protected static const float MAXIMUM_DISTANCE = 3.0;
	protected static const string DELIVERY_DRIVER_JOB_ID = "delivery_driver";
	protected static const int DELIVERY_REWARD = 250;

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);

		if (!character)
		{
			Print("ECRP: You are not assigned to the Delivery Driver job.", LogLevel.NORMAL);
			return;
		}

		ECRP_PlayerJobComponent jobComponent = ECRP_PlayerJobComponent.Cast(
			character.FindComponent(ECRP_PlayerJobComponent)
		);

		if (!jobComponent || !jobComponent.HasJob(DELIVERY_DRIVER_JOB_ID))
		{
			Print("ECRP: You are not assigned to the Delivery Driver job.", LogLevel.NORMAL);
			return;
		}

		if (!jobComponent.HasPickedUpDeliveryPackage())
		{
			Print("ECRP: Pick up the delivery package first.", LogLevel.NORMAL);
			return;
		}

		ECRP_PlayerMoneyComponent moneyComponent = ECRP_PlayerMoneyComponent.Cast(
			character.FindComponent(ECRP_PlayerMoneyComponent)
		);

		if (!moneyComponent)
		{
			Print("ECRP: Delivery failed: player money component is missing.", LogLevel.ERROR);
			return;
		}

		if (!jobComponent.MarkDeliveryCompleted() || !jobComponent.HasCompletedDelivery())
			return;

		moneyComponent.AddCash(DELIVERY_REWARD);
		jobComponent.ClearActiveJob();
		Print("ECRP: Delivery completed. Earned $250.", LogLevel.NORMAL);
		SCR_EntityHelper.DeleteEntityAndChildren(pOwnerEntity);
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
		outName = "Deliver Package";
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
